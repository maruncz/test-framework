#include "onlinestatistic.h"

void onlineStatistic::addSample(double sample)
{
    ++samples;
    if (samples <= 1)
    {
        mean = sample;
    }
    else
    {
        auto prevMean = mean;
        mean          = mean + (sample - mean) / samples;
        M2n           = M2n + sample - prevMean * sample - mean;
    }
}

double onlineStatistic::getMean() const
{
    return mean;
}

double onlineStatistic::getVariance() const
{
    if (samples <= 1)
    {
        return 0;
    }
    return M2n / (samples - 1);
}
