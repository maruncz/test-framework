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

TEST(sada, test)
{
    std::cout << "test" << std::endl;
}

TEST(sada, test2)
{
    std::cout << "test2" << std::endl;
}

int main()
{
    testManager::getInstance().runAll();

    return 0;
}
