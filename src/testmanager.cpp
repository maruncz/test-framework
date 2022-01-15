#include "testmanager.h"
#include "testbase.h"

testManager &testManager::getInstance()
{
    static testManager instance;
    return instance;
}

void testManager::insertTestCase(const testBase *testCase)
{
    map[testCase->getTestSuite()].insert(
        std::make_pair(testCase->getTestCase(), testCase));
}

void testManager::runAll() const
{
    for (auto &suite : map)
    {
        for (auto &test : suite.second)
        {
            test.second->runCase();
        }
    }
}
