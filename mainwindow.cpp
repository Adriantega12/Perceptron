#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);



    // Inicializar plot
    points = new QCPGraph( ui->perceptronPlot->xAxis, ui->perceptronPlot->yAxis );
    points->setLineStyle(QCPGraph::lsNone);
    points->setScatterStyle(QCPScatterStyle::ssCircle);
    points->setPen( QPen(Qt::red ) );

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
        ui->perceptronPlot->replot();
        }
    }
