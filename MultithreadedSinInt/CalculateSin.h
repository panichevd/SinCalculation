#ifndef CALCULATESIN_H
#define CALCULATESIN_H

#include "ThreadPool.h"

//  We should pass threadPool object in case we want to stop the calculation
//  a is starting point, b - end point, steps - is the number of intervals in the method
double CalculateIntegralSin(ThreadPool &threadPool, double a, double b, unsigned steps);

#endif // CALCULATESIN_H
