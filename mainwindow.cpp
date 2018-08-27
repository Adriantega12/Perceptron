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
    onScreenW1 = /*QRandomGenerator::global()->generateDouble()*/0.1;
    onScreenW2 = 0.02;
    learningRate = ui->lrSB->value();
    maxEpochs = ui->meSB->value();

    ui->w1ValLbl->setText( QString::number( onScreenW1 ) );
    ui->w2ValLbl->setText( QString::number( onScreenW2 ) );
    }

void MainWindow::on_trainBttn_clicked() {
    bool done = false;
    double error;

    perp.setup( onScreenW1, onScreenW2 );

    while ( !done ) {
        done = true;
        for ( int j = 0; j < perp.getSizeOfDataVector(); ++j ) {
            error = perp.valueAt(j) - 0/*pw(xj)*/;
            if ( error != 0 ) {
                done = false;
                //perp.setWeight1( perp.getWeight1() + perp.getWeight1() * learningRate *  );
                onScreenW1 = onScreenW1 + onScreenW1 * learningRate * perp.keyAt( j );
                onScreenW1 = onScreenW1 + onScreenW1 * learningRate * perp.keyAt( j );
                }
            }
        }
    }
