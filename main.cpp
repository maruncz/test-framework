#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <numeric>
#include <thread>
#include <vector>

/*class testBase
{
public:
    testBase() { tests.push_back(this); }

    static void runAll()
    {
        for (auto e : tests)
        {
            e->run();
        }
    }

protected:
    virtual void run() = 0;

private:
    static std::vector<testBase *> tests;
};

std::vector<testBase *> testBase::tests{};

class testA : public testBase
{
protected:
    void run() override { std::cout << "testA\n"; }
};

testA test_a;

class testB : public testBase
{
protected:
    void run() override { std::cout << "testB\n"; }
};

testB test_b;*/

// using hrc = std::chrono::high_resolution_clock;
using timer    = std::chrono::steady_clock;
using duration = std::chrono::duration<double, std::ratio<1, 1>>;

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

static void test()
{
    /*std::vector<int> tmp;
    tmp.reserve(10);
    DoNotOptimize(tmp);*/
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
    // testBase::runAll();

#if 0
    std::map<duration, unsigned> hist;
    duration mean;
    auto last_time_point = timer::now();
    double M2n=0;
    unsigned long count = 0;
    //bool run            = true;

    while (true)
    {
        auto start = timer::now();
        test();
        auto end    = timer::now();
        auto sample = end - start;
        hist[sample]++;
        ++count;
        auto now = timer::now();
        if (count <= 1)
        {
            mean = sample;
            if((now - last_time_point) > std::chrono::seconds(1))
            {
                std::cout << "iteration:\t" << count << " mean:\t" << mean.count() << std::endl;
                last_time_point = now;
            }
        }
        else
        {
            // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm
            auto mean_prev = mean;
            mean           = mean + (sample - mean) / count;
            M2n = M2n + (sample - mean_prev).count() * (sample - mean).count();
            double s2n    = M2n / (count - 1);
            double stddev = sqrt(s2n);
            if((now - last_time_point) > std::chrono::seconds(1))
            {
                std::cout << "iteration:\t" << count << " mean:\t" << mean.count() << " stddev:\t" << stddev << std::endl;
                last_time_point = now;
            }
            if(count > 3)
            {
                if((10*stddev) < mean.count())
                {
                    break;
                }
            }
        }
    }
#endif
#if 0
    for (int i = 0; i < 8000000; ++i)
    {
        auto start = hrc::now();
        //auto tmp = pow(i%500,i%5);
        std::vector<int> tmp;
        tmp.reserve(10);
        DoNotOptimize(tmp);
        auto end   = hrc::now();
        hist[end - start]++;
    }

    auto res = std::max_element(hist.begin(), hist.end(),
                                [](const std::pair<hrc::duration, unsigned> &p1,
                                   const std::pair<hrc::duration, unsigned> &p2)
                                { return p1.second < p2.second; });

    double scale_value  = 50.0 / res->second;
    unsigned size_value = ceil(log10(res->second));
    unsigned size_time =
        ceil(log10(std::chrono::duration_cast<std::chrono::nanoseconds>(
                       hist.rbegin()->first)
                       .count()));

    std::map<hrc::duration, unsigned> cum_hist;

    std::partial_sum(hist.begin(),hist.end(),cum_hist.begin());


    for (const auto &e : hist)
    {
        /*std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         e.first)
                         .count()
                  << ": " << e.second << "\n";*/
        auto pad = "#################################################\0";

        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(e.first)
                .count();
        int graph = e.second * scale_value;
        printf("%*li: %*i %.*s\n", size_time, time, size_value, e.second, graph,
               pad);
    }
#endif

    return 0;
}
