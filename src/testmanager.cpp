#include "testmanager.h"
#include "testbase.h"

testManager &testManager::getInstance()
{
    static testManager instance;
    return instance;
}

void testManager::insertTestCase(testAbstract *testCase)
{
    tests.push_back(testCase);
}

void testManager::insertBenchmarkCase(testAbstract *testCase)
{
    benchmarks.push_back(testCase);
}

void testManager::runAllTests() const
{
    for (auto test : tests)
    {
        test->run();
    }
}

void testManager::runAllBenchmarks() const
{
    for (auto benchmark : benchmarks)
    {
        benchmark->run();
    }
}
