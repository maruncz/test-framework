#ifndef BENCHMARKBASE_H
#define BENCHMARKBASE_H

#include "benchmarksettings.h"
#include "onlinestatistic.h"
#include "testabstract.h"
#include "testmanager.h"
#include "timing.h"
#include <cinttypes>

//#define DEBUG_ITER

template<class Tp>
inline void DoNotOptimize(Tp const &value)
{
    asm volatile("" : : "r,m"(value) : "memory");
}

template<class Tp>
inline void DoNotOptimize(Tp &value)
{
#if defined(__clang__)
    asm volatile("" : "+r,m"(value) : : "memory");
#else
    asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

class benchmarkBase : public testAbstract
{
public:
    benchmarkBase(const std::string &inTestSuite, const std::string &inTestCase)
        : testAbstract(inTestSuite, inTestCase)
    {
        testManager::getInstance().insertBenchmarkCase(this);
    }

    benchmarkBase(const benchmarkBase &o) = delete;

    void run() override
    {
        setUp();
        onlineStatistic stats;
        bool minTime;
        bool maxTime;
        double elapsedTime{0.0};
        bool isConverging;
        bool enoughIterations;
        bool isMeanPreciseEnough;
        do
        {
            auto lastVariance = stats.getVariance();
            auto start = timing::now();
            runBenchmark();
            auto end = timing::now();
            auto sample = timing::duration(start, end);
            stats.addSample(sample);
            elapsedTime += sample;
            minTime = elapsedTime > BENCHMARK_MIN_TIME;
            maxTime = elapsedTime > BENCHMARK_MAX_TIME;
            isConverging = (stats.getVariance() / lastVariance)
                           < BENCHMARK_CONVERGENCE_RATIO;
            enoughIterations = stats.getSamples() >= BENCHMARK_MIN_ITER;
            isMeanPreciseEnough = (stats.getMean() / stats.getStdDev())
                                  > BENCHMARK_MEAN_PRECISION;

#ifdef DEBUG_ITER
            printf("iter: %g %g\n", sample, elapsedTime);
#endif
            if (maxTime)
            {
                break;
            }
            if (minTime)
            {
                if (!isConverging)
                {
                    if (isMeanPreciseEnough)
                    {
                        break;
                    }
                    if (enoughIterations)
                    {
                        break;
                    }
                }
            }
        } while (true);
        tearDown();
        printf("%10s/%20s %9u %12e %12e %12e %12e %12e\n",
               getTestSuite().c_str(), getTestCase().c_str(),
               stats.getSamples(), stats.getMean(), stats.getMedian(),
               stats.quantile(0.5), stats.quantile(0.9), stats.quantile(0.99));
        // stats.printHist();
        fflush(stdout);
    }

protected:
    virtual void runBenchmark() = 0;
    virtual void setUp() {}
    virtual void tearDown() {}
};

#endif // BENCHMARKBASE_H
