#ifndef TESTABSTRACT_H
#define TESTABSTRACT_H

#include <string>

#define stringify_helper(s) #s
#define stringify(s) stringify_helper(s)

class testAbstract
{
public:
    testAbstract(const std::string &inTestSuite, const std::string &inTestCase)
        : testSuite(inTestSuite), testCase(inTestCase)
    {}

    virtual ~testAbstract() = default;

    virtual void run() = 0;

    [[nodiscard]] const std::string &getTestSuite() const { return testSuite; }
    [[nodiscard]] const std::string &getTestCase() const { return testCase; }

private:
    const std::string testSuite;
    const std::string testCase;
};

#endif // TESTABSTRACT_H
