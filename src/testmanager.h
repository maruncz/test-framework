#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <iostream>
#include <map>
#include <string>

class testBase;

// https://stackoverflow.com/a/1008289
class testManager
{
public:
    static testManager &getInstance();

    void insertTestCase(testBase const *testCase);

    void runAll() const;

    testManager(testManager const &o) = delete;
    testManager(testManager &&o)      = delete;
    void operator=(testManager const &o) = delete;
    testManager &operator=(testManager &&o) = delete;
    ~testManager()                          = default;

private:
    testManager() = default;

    using casesMap  = std::map<std::string, const testBase *>;
    using suitesMap = std::map<std::string, casesMap>;
    suitesMap map;
};

#endif // TESTMANAGER_H
