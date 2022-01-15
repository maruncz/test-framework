#ifndef TESTBASE_H
#define TESTBASE_H

#include "testabstract.h"
#include <iostream>
#include <map>
#include <string>
#include <utility>

class testBase : public testAbstract
{
public:
    class result
    {
    public:
        explicit result(bool inOk, std::string inMsg = std::string())
            : ok(inOk), msg(std::move(inMsg))
        {
        }

        [[nodiscard]] bool getOk() const { return ok; }
        [[nodiscard]] const std::string &getMsg() const { return msg; }

    private:
        const bool ok;
        const std::string msg;
    };

    testBase(std::string inTestSuite, std::string inTestCase)
        : testAbstract(std::move(inTestSuite), std::move(inTestCase))
    {
        testManager::getInstance().insertTestCase(this);
    }

    ~testBase() override = default;

    void run() const override
    {
        std::cout << "[" << getTestSuite() << ", " << getTestCase() << "] "
                  << "running" << std::endl;
        auto result = runTestCase();
        std::cout << "[" << getTestSuite() << ", " << getTestCase() << "] ";
        if (result.getOk())
        {
            std::cout << "OK" << std::endl;
        }
        else
        {
            std::cout << "failed: " << result.getMsg() << std::endl;
        }
    }

    [[nodiscard]] virtual result runTestCase() const = 0;
};

#endif // TESTBASE_H
