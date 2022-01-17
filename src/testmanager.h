#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <iostream>
#include <map>
#include <string>

class testAbstract;

// https://stackoverflow.com/a/1008289
class testManager
{
public:
    static testManager &getInstance();

    void insertTestCase(testAbstract *testCase);
    void insertBenchmarkCase(testAbstract *testCase);

    void runAllTests() const;
    void runAllBenchmarks() const;

    testManager(testManager const &o) = delete;
    testManager(testManager &&o)      = delete;
    void operator=(testManager const &o) = delete;
    testManager &operator=(testManager &&o) = delete;
    ~testManager()                          = default;

private:
    testManager() = default;

    using casesMap  = std::map<std::string, testAbstract *>;
    using suitesMap = std::map<std::string, casesMap>;
    suitesMap testMap;
    suitesMap benchmarkMap;
};

#endif // TESTMANAGER_H
