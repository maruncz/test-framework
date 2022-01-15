#include <gtest/gtest.h>
#include <limits>
#include <onlinestatistic.h>
#include <random>
#include <vector>

// constexpr double dbl_eps = std::numeric_limits<double>::epsilon();
constexpr double relPrec{1e-7};

TEST(stats, random)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(0, 1000);
    std::vector<double> samples;
    onlineStatistic stats;
    for (int i = 0; i < 1000; ++i)
    {
        auto sample = dist(generator);
        stats.addSample(sample);
        samples.emplace_back(sample);
        if (samples.size() < 2)
        {
            continue;
        }
        double mean{0};
        double variance{0};
        for (auto e : samples)
        {
            mean += e;
        }
        mean /= samples.size();
        ASSERT_NEAR(mean, stats.getMean(), stats.getMean() * relPrec)
            << "iteration: " << i;
        for (auto e : samples)
        {
            variance += (e - mean) * (e - mean);
        }
        variance /= (samples.size() - 1);
        ASSERT_NEAR(variance, stats.getVariance(),
                    stats.getVariance() * relPrec)
            << "iteration: " << i;
    }
}
