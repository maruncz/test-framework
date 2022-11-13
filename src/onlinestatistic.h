#ifndef ONLINESTATISTIC_H
#define ONLINESTATISTIC_H

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <map>
#include <utility>

class onlineStatistic
{
public:
    void addSample(double sample);

    double getMean() const;
    double getVariance() const;
    double getStdDev() const;
    uint32_t getSamples() const;
    double getMedian() const;
    double quantile(double value) const;
    void printHist() const;

private:
    using histSample = std::pair<double, uint32_t>;
    static double roundToDigits(double value, uint8_t digits);
    static double linearInterpolation(double x0, double x1, double y0,
                                      double y1, double point);

    std::map<double, uint32_t> hist;
    double mean{0};
    double M2n{0};
    uint32_t samples{0};
};

#endif // ONLINESTATISTIC_H
