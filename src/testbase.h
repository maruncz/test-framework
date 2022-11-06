#ifndef TESTBASE_H
#define TESTBASE_H

#include "testabstract.h"
#include "testmanager.h"
#include <cstdio>
#include <map>
#include <string>
#include <utility>

class testBase : public testAbstract
{
public:
    class result
    {
    public:
        explicit result(bool inOk, const std::string &inMsg = std::string())
            : ok(inOk), msg(inMsg)
        {}

        [[nodiscard]] bool getOk() const { return ok; }
        [[nodiscard]] const std::string &getMsg() const { return msg; }

    private:
        const bool ok;
        const std::string msg;
    };

    testBase(const std::string &inTestSuite, const std::string &inTestCase)
        : testAbstract(inTestSuite, inTestCase)
    {
        testManager::getInstance().insertTestCase(this);
    }

    ~testBase() override = default;

    void run() override
    {
        printf("[%s, %s] running\n", getTestSuite().c_str(),
               getTestCase().c_str());
        auto result = runTestCase();
        printf("[%s, %s] ", getTestSuite().c_str(), getTestCase().c_str());
        if (result.getOk())
        {
            printf("OK\n");
        }
        else
        {
            printf("failed: %s\n", result.getMsg().c_str());
        }
    }

    [[nodiscard]] virtual result runTestCase() const = 0;
};

#endif // TESTBASE_H
