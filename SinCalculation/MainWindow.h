#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculationthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

private slots:
    void on_StartButton_clicked();
    void on_StopButton_clicked();

private:
    Ui::MainWindow *ui;
    CalculationThread m_calcThread;
};

#endif // MAINWINDOW_H
