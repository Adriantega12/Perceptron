#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicialziar gráfica de error
    ui->errorPlot->addGraph();
    ui->errorPlot->xAxis->setLabel( "Epoch" );
    ui->errorPlot->yAxis->setLabel( "Error acumulado" );

    // Inicializar puntos
    redPoints = new QCPGraph( ui->perceptronPlot->xAxis, ui->perceptronPlot->yAxis );
    bluePoints = new QCPGraph( ui->perceptronPlot->xAxis, ui->perceptronPlot->yAxis );
    redPoints->setLineStyle(QCPGraph::lsNone);
    redPoints->setScatterStyle(QCPScatterStyle::ssCircle);
    redPoints->setPen( QPen(Qt::red) );
    bluePoints->setLineStyle(QCPGraph::lsNone);
    bluePoints->setScatterStyle(QCPScatterStyle::ssCircle);
    bluePoints->setPen( QPen(Qt::blue) );

    // Inicializar puntos de línea
    ui->perceptronPlot->addGraph();
    lineX.push_back(-6);
    lineX.push_back(0);
    lineX.push_back(6);
    lineY.push_back(0);
    lineY.push_back(0);
    lineY.push_back(0);

    points = redPoints;

    // Inicializar plot
    // Ejes
    ui->perceptronPlot->xAxis->setRange(-5, 5);
    ui->perceptronPlot->yAxis->setRange(-5, 5);
    ui->perceptronPlot->xAxis2->setRange(-5, 5);
    ui->perceptronPlot->yAxis2->setRange(-5, 5);
    ui->perceptronPlot->xAxis2->setVisible(true);
    ui->perceptronPlot->yAxis2->setVisible(true);

    ui->perceptronPlot->xAxis->setBasePen( QPen( Qt::gray ) );
    ui->perceptronPlot->yAxis->setBasePen( QPen( Qt::gray ) );
    ui->perceptronPlot->xAxis2->setBasePen( QPen( Qt::gray ) );
    ui->perceptronPlot->yAxis2->setBasePen( QPen( Qt::gray ) );

    ui->perceptronPlot->xAxis->grid()->setZeroLinePen( QPen( Qt::black ) );
    ui->perceptronPlot->yAxis->grid()->setZeroLinePen( QPen( Qt::black ) );

    connect(ui->perceptronPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(plotClick(QMouseEvent*)));
    }

MainWindow::~MainWindow() {
    delete ui;
    //delete points;
    }

void MainWindow::plotClick( QMouseEvent* event ) {
    if(ui->perceptronPlot->axisRect()->rect().contains( event->pos() ) ) {
        double x = ui->perceptronPlot->xAxis->pixelToCoord( event->x() );
        double y = ui->perceptronPlot->yAxis->pixelToCoord( event->y() );
        points->addData( x, y );
        tm.addData( x, y, (ui->redRadBttn->isChecked() ?
                               TrainingModule::RED : TrainingModule::BLUE) );
        qDebug() << x << " " << y;
        ui->perceptronPlot->replot();
        }
    }

void MainWindow::on_redRadBttn_toggled(bool checked) {
    if ( checked ) {
        points = redPoints;
        }
    }

void MainWindow::on_blueRadBttn_toggled(bool checked) {
    if ( checked ) {
        points = bluePoints;
        }
    }

void MainWindow::on_initializeBttn_clicked() {
    double onScreenWeight0 = tm.generateRandomDoubleNumber( -5.0, 5.0 ),
           onScreenWeight1 = tm.generateRandomDoubleNumber( -5.0, 5.0 ),
           onScreenWeight2 = tm.generateRandomDoubleNumber( -5.0, 5.0 );

    // Inicializar pesos
    ui->w0ValLbl->setText( QString::number(onScreenWeight0) );
    ui->w1ValLbl->setText( QString::number(onScreenWeight1) );
    ui->w2ValLbl->setText( QString::number(onScreenWeight2) );
    tm.setup(onScreenWeight0, onScreenWeight1, onScreenWeight2, ui->lrSB->value());

    // Inicializar línea
    lineY[0] = tm.getSlope() * lineX[0] + tm.getIntercept();
    lineY[1] = tm.getSlope() * lineX[1] + tm.getIntercept();
    lineY[2] = tm.getSlope() * lineX[2] + tm.getIntercept();
    ui->perceptronPlot->graph(2)->setData(lineX, lineY);
    ui->perceptronPlot->replot();

    ui->trainBttn->setEnabled(true);

    ui->errorPlot->graph(0)->data()->clear();
    ui->errorPlot->replot();
    ui->errorPlot->repaint();
    }

void MainWindow::on_trainBttn_clicked() {
    /*Bunch of enable code here*/
    bool done = false;
    int error = 0;
    int epochs = 0;
    int maxEpochs = ui->meSB->value();
    int errorPerEpoch;

    while (epochs < maxEpochs and !done) {
        done = true;
        errorPerEpoch = 0;
        for (unsigned int j = 0; j < tm.getSizeOfTrainingSet(); ++j) {
            int type = tm.getDataTypeAt(j);
            int pw = tm.perceptWeight(j);
            error = type - pw;
            if (error != 0) {
                done = false;
                tm.update(j, error);
                ui->w0ValLbl->setText( QString::number(tm.getWeight0()) );
                ui->w1ValLbl->setText( QString::number(tm.getWeight1()) );
                ui->w2ValLbl->setText( QString::number(tm.getWeight2()) );
                lineY[0] = tm.getSlope() * lineX[0] + tm.getIntercept();
                lineY[1] = tm.getSlope() * lineX[1] + tm.getIntercept();
                lineY[2] = tm.getSlope() * lineX[2] + tm.getIntercept();
                ui->perceptronPlot->graph(2)->setData(lineX, lineY);
                ui->perceptronPlot->replot();
                ui->perceptronPlot->repaint();
                errorPerEpoch++;
                }
            ui->errorPlot->graph(0)->addData(epochs, errorPerEpoch);
            ui->errorPlot->replot();
            ui->errorPlot->repaint();
            ui->errorPlot->rescaleAxes();
            }
        epochs++;
        ui->currentEpochValLbl->setText( QString::number(epochs) );
        }

    ui->convValLbl->setText( QString::number(epochs) );
    }
