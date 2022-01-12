#ifndef ONLINESTATISTIC_H
#define ONLINESTATISTIC_H

#include <cstdint>
#include <cstddef>

class onlineStatistic
{
public:

    void addSample(double sample);

    double getMean() const;
    double getVariance() const;

private:
    double mean{0};
    double M2n{0};
    size_t samples{0};
};

#endif // ONLINESTATISTIC_H
