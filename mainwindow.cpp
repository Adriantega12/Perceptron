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
