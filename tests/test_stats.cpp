#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <onlinestatistic.h>
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>
#include <vector>

// constexpr double dbl_eps = std::numeric_limits<double>::epsilon();
constexpr double relPrec{1e-7};

TEST(stats, random)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(0, 1000);
    std::vector<double> samples;
    onlineStatistic stats;
    for (int i = 0; i < 100; ++i)
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
        ASSERT_NEAR(mean, stats.getMean(), stats.getMean() * relPrec);

        for (auto e : samples)
        {
            variance += (e - mean) * (e - mean);
        }
        variance /= (samples.size() - 1);
        ASSERT_NEAR(variance, stats.getVariance(),
                    stats.getVariance() * relPrec);

        double median{0};
        auto center = samples.size() / 2;
        std::sort(samples.begin(), samples.end());
        if ((samples.size() % 2) == 0)
        {
            median = (samples.at(center - 1) + samples.at(center)) / 2;
        }
        else
        {
            median = samples.at(center);
        }

        double q09 = samples.at(samples.size() * 0.9);

        auto median_stat = stats.getMedian();
        ASSERT_NEAR(median, median_stat, median * 2e-2);
//        std::cout << sample << '\t' << stats.getMean() << "\t"
//                  << stats.getMedian() << '\t' << stats.getVariance() << "\t"
//                  << stats.quantile(0.5) << "\t" << stats.quantile(0.9) << "\t"
//                  << stats.quantile(0.99) << "\t\t" << mean << '\t' << median
//                  << '\t' << variance << "\t\t" << q09 << '\n';
    }
    //stats.printHist();
    /*for(auto e : samples)
    {
        std::cout << e <<";\n";
    }*/
    return result(true);
}
