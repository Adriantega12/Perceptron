#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
//#include <QRandomGenerator>

#include "qcustomplot.h"
#include "trainingmodule.h"

namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        QCPGraph* points;
        QCPGraph* redPoints;
        QCPGraph* bluePoints;
        double onScreenW1;
        double onScreenW2;
        double learningRate;
        int maxEpochs;

        TrainingModule tm;
        QVector<double> lineX;
        QVector<double> lineY;

    public slots:
        void plotClick( QMouseEvent* );

    private slots:
        void on_redRadBttn_toggled(bool checked);
        void on_blueRadBttn_toggled(bool checked);
        void on_initializeBttn_clicked();
        void on_trainBttn_clicked();
};

#endif // MAINWINDOW_H
