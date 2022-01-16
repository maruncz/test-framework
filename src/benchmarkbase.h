#ifndef BENCHMARKBASE_H
#define BENCHMARKBASE_H

#include "benchmarksettings.h"
#include "onlinestatistic.h"
#include "testabstract.h"
#include "timing.h"

template<class Tp> inline void DoNotOptimize(Tp const &value)
{
    asm volatile("" : : "r,m"(value) : "memory");
}

template<class Tp> inline void DoNotOptimize(Tp &value)
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
        bool minTime;
        bool maxTime;
        double elapsedTime{0.0};
        bool isConverging;
        bool enoughIterations;
        bool isMeanPreciseEnough;
        do
        {
            auto lastVariance = stats.getVariance();
            auto start        = timePoint::now();
            runBenchmark();
            auto end    = timePoint::now();
            auto sample = timePoint::duration(start, end);
            stats.addSample(sample);
            elapsedTime += sample;
            minTime      = elapsedTime > BENCHMARK_MIN_TIME;
            maxTime      = elapsedTime > BENCHMARK_MAX_TIME;
            isConverging = (stats.getVariance() / lastVariance) <
                           BENCHMARK_CONVERGENCE_RATIO;
            enoughIterations    = stats.getSamples() >= BENCHMARK_MIN_ITER;
            isMeanPreciseEnough = (stats.getMean() / stats.getStdDev()) >
                                  BENCHMARK_MEAN_PRECISION;
#ifndef NDEBUG
            //std::cout << sample << ", " << elapsedTime << "\n";
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
        std::cout << getTestSuite() << "/" << getTestCase()
                  << " \tsamples: " << stats.getSamples() << " \t"
                  << stats.getMean() << " \t" << stats.getStdDev() << std::endl;
    }

    virtual void runBenchmark() const = 0;
};

#endif // BENCHMARKBASE_H
