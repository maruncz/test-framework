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
            : msg(inMsg), ok(inOk)
        {
        }

        bool getOk() const { return ok; }
        const std::string &getMsg() const { return msg; }

    private:
        const std::string msg;
        const bool ok;
    };

    testBase(const std::string &inTestSuite, const std::string &inTestCase)
        : testAbstract(inTestSuite, inTestCase)
    {
        testManager::getInstance().insertTestCase(this);
    }

    ~testBase() override = default;

    bool run() override
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
        fflush(stdout);
        return result.getOk();
    }

    virtual result runTestCase() const = 0;
};

#endif // TESTBASE_H
