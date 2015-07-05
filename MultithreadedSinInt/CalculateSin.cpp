#include "CalculateSin.h"
#include "ThreadPool.h"
#include <cmath>
#include <numeric>

using std::accumulate;

void SaveSin(double x, double &placement)
{
    placement = sin(x);
}

double CalculateIntegralSin(ThreadPool &threadPool, double a, double b, unsigned steps)
{
    double h = (b - a) / steps;

    vector<double> pointsResult(steps);
    queue<pair<double, double &>> params;
    for (unsigned i = 0; i < steps; ++i)
        params.emplace(pair<double, double &>(a + h*i, pointsResult[i]));

    threadPool.Run(&SaveSin, params);

    return (h/2) *
        (pointsResult[0] + 2*accumulate(pointsResult.begin() + 1, pointsResult.end() - 1, 0.0) + pointsResult[steps - 1]);
}


