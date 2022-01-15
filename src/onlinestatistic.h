#ifndef ONLINESTATISTIC_H
#define ONLINESTATISTIC_H

#include <cstddef>
#include <cstdint>

class onlineStatistic
{
public:
    void addSample(double sample);

    [[nodiscard]] double getMean() const;
    [[nodiscard]] double getVariance() const;

private:
    double mean{0};
    double M2n{0};
    size_t samples{0};
};

#endif // ONLINESTATISTIC_H
