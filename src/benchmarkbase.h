#ifndef BENCHMARKBASE_H
#define BENCHMARKBASE_H

#include "onlinestatistic.h"
#include "testabstract.h"
#include "timing.h"

class benchmarkBase : public testAbstract
{
public:
    class result
    {
    public:
        void addSample(double sample) { stats.addSample(sample); }

    private:
        onlineStatistic stats;
    };

    benchmarkBase(std::string inTestSuite, std::string inTestCase)
        : testAbstract(std::move(inTestSuite), std::move(inTestCase))
    {
        testManager::getInstance().insertBenchmarkCase(this);
    }

    void run() const override
    {
        onlineStatistic stats;
        // bool isConverging;
        // bool enoughIterations;
        // bool isMeanPreciseEnough;
        do
        {
            // auto lastVariance = stats.getVariance();
            auto start = timePoint::now();
            runBenchmark();
            auto end    = timePoint::now();
            auto sample = timePoint::duration(start, end);
#ifndef NDEBUG
            std::cout << sample << std::endl;
#endif
            stats.addSample(sample);
            // isConverging     = (stats.getVariance() / lastVariance) < 0.9;
            // enoughIterations = stats.getSamples() >= 10;
            // isMeanPreciseEnough = (stats.getMean() / stats.getStdDev()) > 3;
        } while (stats.getSamples() < 10);
        std::cout << getTestSuite() << "/" << getTestCase()
                  << " \tsamples: " << stats.getSamples() << " \t"
                  << stats.getMean() << " \t" << stats.getStdDev() << std::endl;
    }

    virtual void runBenchmark() const = 0;
};

#endif // BENCHMARKBASE_H
