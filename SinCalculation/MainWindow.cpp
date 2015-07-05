#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_calcThread(this)
{
    ui->setupUi(this);
    setWindowTitle("Sin Intergal Calculator");
    setFixedSize(size());
    connect(&m_calcThread, SIGNAL(Calculated(double)), ui->lcdNumber, SLOT(display(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    if (!m_calcThread.isRunning())
    {
        m_calcThread.setArgs(this->ui->threadsSpinBox->value(),
                             this->ui->aSpinBox->value(),
                             this->ui->bSpinBox->value(),
                             this->ui->stepsSpinBox->value());
        m_calcThread.start();
    }
    else
        QMessageBox::information(this, "Error",
                                 "Calculation is already running", QMessageBox::Ok);
}

void MainWindow::on_StopButton_clicked()
{
	//  If there are any calculations that running right now - stop them and finish the thread
    if (m_calcThread.isRunning())
    {		
        m_calcThread.StopCalculations();
        m_calcThread.wait();
        QMessageBox::information(this, "Stop",
                                 "Calculation stopped", QMessageBox::Ok);
    }
    else
        QMessageBox::information(this, "Stop",
                                 "No calculations are running", QMessageBox::Ok);
}

