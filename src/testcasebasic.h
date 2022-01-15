#ifndef TESTCASEBASIC_H
#define TESTCASEBASIC_H

#include "testbase.h"
#include <utility>

#define TEST(test_suite_name, test_case_name)                               \
    class testCaseBasic##_##test_suite_name##_##test_case_name              \
        : public testBase                                                   \
    {                                                                       \
    public:                                                                 \
        testCaseBasic##_##test_suite_name##_##test_case_name(               \
            std::string inTestSuite, std::string inTestCase)                \
            : testBase(std::move(inTestSuite), std::move(inTestCase))       \
        {                                                                   \
        }                                                                   \
        void run() const override;                                          \
    };                                                                      \
                                                                            \
    testCaseBasic##_##test_suite_name##_##test_case_name                    \
        test_suite_name##_##test_case_name(stringify(test_suite_name),      \
                                           stringify(test_case_name));      \
                                                                            \
    inline void testCaseBasic##_##test_suite_name##_##test_case_name::run() \
        const

#endif // TESTCASEBASIC_H
