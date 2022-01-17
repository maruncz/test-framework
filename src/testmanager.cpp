#include "testmanager.h"
#include "testbase.h"

testManager &testManager::getInstance()
{
    static testManager instance;
    return instance;
}

void testManager::insertTestCase(testAbstract *testCase)
{
    testMap[testCase->getTestSuite()].insert(
        std::make_pair(testCase->getTestCase(), testCase));
}

void testManager::insertBenchmarkCase(testAbstract *testCase)
{
    benchmarkMap[testCase->getTestSuite()].insert(
        std::make_pair(testCase->getTestCase(), testCase));
}

void testManager::runAllTests() const
{
    for (auto &suite : testMap)
    {
        for (auto &test : suite.second)
        {
            test.second->run();
        }
    }
}

void testManager::runAllBenchmarks() const
{
    for (auto &suite : benchmarkMap)
    {
        for (auto &test : suite.second)
        {
            test.second->run();
        }
    }
}
