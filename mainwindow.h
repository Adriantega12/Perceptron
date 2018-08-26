#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"

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

    public slots:
        void plotClick( QMouseEvent* );
    };

#endif // MAINWINDOW_H
