#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);



    // Inicializar puntos
    redPoints = new QCPGraph( ui->perceptronPlot->xAxis, ui->perceptronPlot->yAxis );
    bluePoints = new QCPGraph( ui->perceptronPlot->xAxis, ui->perceptronPlot->yAxis );
    redPoints->setLineStyle(QCPGraph::lsNone);
    redPoints->setScatterStyle(QCPScatterStyle::ssCircle);
    redPoints->setPen( QPen(Qt::red) );
    bluePoints->setLineStyle(QCPGraph::lsNone);
    bluePoints->setScatterStyle(QCPScatterStyle::ssCircle);
    bluePoints->setPen( QPen(Qt::blue) );

    points = redPoints;

    // Inicializar plot
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
        perp.addData( x, y, (ui->redRadBttn->isChecked() ?
                                 Perceptron::Type::RED : Perceptron::Type::BLUE) );
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
    double onScreenWeight1 = 0.01,
           onScreenWeight2 = 0.1;
    ui->w1ValLbl->setText( QString::number(onScreenWeight1) );
    ui->w2ValLbl->setText( QString::number(onScreenWeight2) );
    tm.setup(onScreenWeight1, onScreenWeight2, ui->lrSB->value());
    ui->trainBttn->setEnabled(true);
    }

void MainWindow::on_trainBttn_clicked() {
    /*Bunch of enable code here*/
    bool done = false;
    int error = 0;
    int epochs = 0;
    int maxEpochs = ui->meSB->value();

    while (epochs < maxEpochs and !done) {
        done = true;
        for (unsigned int j = 0; j < tm.getSizeOfTrainingSet(); ++j) {
            error = tm.getDataTypeAt(j) - tm.perceptWeight(j);
            if (error != 0) {
                done = false;
                tm.update(j, error);
                ui->w1ValLbl->setText( QString::number(tm.getWeight1()) );
                ui->w2ValLbl->setText( QString::number(tm.getWeight2()) );
                }
            }
        epochs++;
        ui->currentEpochValLbl->setText( QString::number(epochs) );
        }

    ui->convValLbl->setText( QString::number(epochs) );
    }
