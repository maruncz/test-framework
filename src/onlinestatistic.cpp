#include "onlinestatistic.h"
#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <limits>

void onlineStatistic::addSample(double sample)
{
    ++(hist[roundToDigits(sample, 5)]);
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
        return std::numeric_limits<double>::max();
    }
    return M2n / (samples - 1);
}

double onlineStatistic::getStdDev() const
{
    return std::sqrt(getVariance());
}

uint32_t onlineStatistic::getSamples() const
{
    return samples;
}

double onlineStatistic::getMedian() const
{
    /*size_t sum_samples = 0;
    for (auto it = hist.begin(); it != hist.end(); ++it)
    {
        size_t nextSumOfSamples = sum_samples + it->second;
        if (nextSumOfSamples > samples / 2)
        {
            if ((hist.size() % 2) == 0)
            {
                auto prev = it;
                --prev;
                return (prev->first + it->first) / 2.0;
            }
            else
            {
                return it->first;
            }
        }
        sum_samples = nextSumOfSamples;
    }*/

    uint32_t sum_samples = 0;
    for (auto it = hist.begin(); it != hist.end(); ++it)
    {
        uint32_t nextSumOfSamples = sum_samples + it->second;
        if (nextSumOfSamples > samples / 2)
        {
            auto prev = it;
            --prev;
            return linearInterpolation(sum_samples, nextSumOfSamples,
                                       prev->first, it->first, samples / 2.0);
        }
        sum_samples = nextSumOfSamples;
    }

    return 0;
}

double onlineStatistic::quantile(double value) const
{
    double point         = (static_cast<double>(samples) * value);
    uint32_t sum_samples = 0;
    for (auto it = hist.begin(); it != hist.end(); ++it)
    {
        uint32_t nextSumOfSamples = sum_samples + it->second;
        if (nextSumOfSamples > point)
        {
            auto prev = it;
            --prev;
            return linearInterpolation(sum_samples, nextSumOfSamples,
                                       prev->first, it->first, point);
        }
        sum_samples = nextSumOfSamples;
    }
    return 0;
}

void onlineStatistic::printHist() const
{
    for (const auto &e : hist)
    {
        printf("%4e %" PRIu32 ";\n", e.first, e.second);
    }
}

double onlineStatistic::roundToDigits(double value, uint8_t digits)
{
    double factor =
        std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
    return std::round(value * factor) / factor;
}

double onlineStatistic::linearInterpolation(double x0, double x1, double y0,
                                            double y1, double point)
{
    return (y0 + (point - x0) * ((y1 - y0) / (x1 - x0)));
}
