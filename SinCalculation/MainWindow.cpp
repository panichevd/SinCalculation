#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_calcThread(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Sin Intergal Calculator");
    setFixedSize(size());
    m_calcThread = new CalculationThread(this);
    connect(m_calcThread, SIGNAL(Calculated(double)), ui->lcdNumber, SLOT(display(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    if (this->ui->aSpinBox->value() > this->ui->bSpinBox->value())
    {
        QMessageBox::information(this, "Error",
                                 "Start point cannot be more than end point",
                                 QMessageBox::Ok);
        return;
    }

    if (m_calcThread->isRunning())
    {
        QMessageBox::information(this, "Error",
                                 "Calculation is already running", QMessageBox::Ok);
        return;
    }

    m_calcThread->setArgs(this->ui->threadsSpinBox->value(),
                          this->ui->aSpinBox->value(),
                          this->ui->bSpinBox->value(),
                          this->ui->stepsSpinBox->value());
    m_calcThread->start();
}

void MainWindow::on_StopButton_clicked()
{
	//  If there are any calculations that running right now - stop them and finish the thread
    if (m_calcThread->isRunning())
    {		
        m_calcThread->StopCalculations();
        m_calcThread->wait();
        QMessageBox::information(this, "Stop",
                                 "Calculation stopped", QMessageBox::Ok);
    }
    else
        QMessageBox::information(this, "Stop",
                                 "No calculations are running", QMessageBox::Ok);
}

