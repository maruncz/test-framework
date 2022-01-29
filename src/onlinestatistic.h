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

    [[nodiscard]] double getMean() const;
    [[nodiscard]] double getVariance() const;
    [[nodiscard]] double getStdDev() const;
    [[nodiscard]] size_t getSamples() const;
    [[nodiscard]] double getMedian() const;
    [[nodiscard]] double quantile(double value) const;
    void printHist() const;

private:
    using histSample = std::pair<double, uint32_t>;
    static double roundToDigits(double value, uint8_t digits);
    static double linearInterpolation(double x0, double x1, double y0,
                                      double y1, double point);

    double mean{0};
    double M2n{0};
    size_t samples{0};
    std::map<double, uint32_t> hist;
};

#endif // ONLINESTATISTIC_H
