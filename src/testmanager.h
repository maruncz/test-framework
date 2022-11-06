#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <iterator>
#include <string>
#include <vector>

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
    testManager(testManager &&o) = delete;
    void operator=(testManager const &o) = delete;
    testManager &operator=(testManager &&o) = delete;
    ~testManager() = default;

private:
    testManager() = default;

    std::vector<testAbstract *> tests;
    std::vector<testAbstract *> benchmarks;
};

#endif // TESTMANAGER_H
