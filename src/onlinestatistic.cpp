#include "onlinestatistic.h"
#include <cmath>

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
        M2n           = M2n + (sample - prevMean) * (sample - mean);
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

double onlineStatistic::getStdDev() const
{
    return std::sqrt(getVariance());
}

size_t onlineStatistic::getSamples() const
{
    return samples;
}
