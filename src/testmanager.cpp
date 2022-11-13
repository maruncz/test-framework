#include "testmanager.h"
#include "testabstract.h"

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

bool testManager::runAllTests() const
{
    bool ok = true;
    for (auto &test : tests)
    {
        ok &= test->run();
    }
    return ok;
}

void testManager::runAllBenchmarks() const
{
    printf("%10s/%-20s %9s %12s %12s %12s %12s %12s %12s\n", "suite name",
           "test name", "samples", "mean", "median", "q0.5", "q0.9", "q0.99", "total time");
    fflush(stdout);
    for (auto &benchmark : benchmarks)
    {
        benchmark->run();
    }
}
