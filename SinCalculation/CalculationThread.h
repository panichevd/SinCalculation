#ifndef CALCULATIONTHREAD_H
#define CALCULATIONTHREAD_H

#include <QThread>
#include "../MultithreadedSinInt/CalculateSin.h"

//  Thread that handles calculation (threads in thread poll) and final result
class CalculationThread : public QThread
{
    Q_OBJECT
public:
    explicit CalculationThread(QObject *parent = 0);
    void StopCalculations();
    void setArgs(unsigned threadsNum, double a, double b, unsigned steps);

signals:
    void Calculated(double);
public slots:

private:
    ThreadPool m_threadPool;
    double m_a;
    double m_b;
    unsigned m_steps;

    void run();
};

#endif // CALCULATIONTHREAD_H
