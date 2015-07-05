#include "calculationthread.h"

CalculationThread::CalculationThread(QObject *parent) :
    QThread(parent), m_threadPool(1)
{
}

void CalculationThread::run()
{
    double res = CalculateIntegralSin(m_threadPool, m_a, m_b, m_steps);
	//  If result is correct - send signal
    if (!m_threadPool.Stopped())
        emit Calculated(res);
}

void CalculationThread::setArgs(unsigned threadsNum, double a, double b, unsigned steps)
{
    m_threadPool = ThreadPool(threadsNum); // move assignment operator is used
    m_a = a;
    m_b = b;
    m_steps = steps;
}

void CalculationThread::StopCalculations()
{
    m_threadPool.Stop();
}
