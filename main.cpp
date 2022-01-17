#include "benchmarkbasic.h"
#include "benchmarkfixture.h"
#include "testcasebasic.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <numeric>
#include <thread>
#include <vector>

/*
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
}*/

TEST(sada, test)
{
    std::cout << "test" << std::endl;
    return result{true};
}

TEST(sada, test2)
{
    std::cout << "test2" << std::endl;
    return result{false};
}

BENCHMARK(bench, bench)
{
    std::this_thread::sleep_for(std::chrono::microseconds(1));
}

class benchmark_TF : public benchmarkBase
{
    using benchmarkBase::benchmarkBase;

protected:
    void setUp() override { std::cout << "setup" << std::endl; }
    void tearDown() override { std::cout << "teardown" << std::endl; }
};

BENCHMARK_F(benchmark_TF, bench, benchF)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    // testManager::getInstance().runAllTests();
    testManager::getInstance().runAllBenchmarks();

    return 0;
}
