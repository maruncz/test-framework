#ifndef TESTBASE_H
#define TESTBASE_H

#include "testmanager.h"
#include <iostream>
#include <map>
#include <string>
#include <utility>

#define stringify_helper(s) #s
#define stringify(s) stringify_helper(s)

class testBase
{
public:
    testBase(std::string inTestSuite, std::string inTestCase)
        : testSuite(std::move(inTestSuite)), testCase(std::move(inTestCase))
    {
        testManager::getInstance().insertTestCase(this);
    }

    virtual ~testBase() = default;

    virtual void runCase() const
    {
        std::cout << "[" << testSuite << ", " << testCase << "] "
                  << "running" << std::endl;
        run();
        std::cout << "[" << testSuite << ", " << testCase << "] "
                  << "finished" << std::endl;
    }

    virtual void run() const = 0;

    [[nodiscard]] const std::string &getTestSuite() const { return testSuite; }

    [[nodiscard]] const std::string &getTestCase() const { return testCase; }

private:
    const std::string testSuite;
    const std::string testCase;
};

#endif // TESTBASE_H
