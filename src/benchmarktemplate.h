#ifndef BENCHMARKTEMPLATE_H
#define BENCHMARKTEMPLATE_H

#include "benchmarkbase.h"

template<typename T> class testWithParam : public benchmarkBase
{
public:
    testWithParam(const std::string &inTestSuite, const std::string &inTestCase,
                  const T &param)
        : benchmarkBase(inTestSuite, inTestCase), param(param)
    {
    }

    const T &getParam() { return param; }

    using paramType = T;

private:
    const T param;
};

#define BENCHMARK_T(fixture_name, test_suite_name, test_case_name)         \
    class benchmarkFixture##_##test_suite_name##_##test_case_name          \
        : public fixture_name                                              \
    {                                                                      \
    public:                                                                \
        benchmarkFixture##_##test_suite_name##_##test_case_name(           \
            const std::string &inTestSuite, const std::string &inTestCase, \
            const typename fixture_name::paramType &inParam)               \
            : fixture_name(inTestSuite, inTestCase, inParam)               \
        {                                                                  \
        }                                                                  \
                                                                           \
        void runBenchmark() override;                                      \
    };                                                                     \
                                                                           \
    inline void benchmarkFixture##_##test_suite_name##_##test_case_name::  \
        runBenchmark()

#define INSTANTIATE_TEMPLATE(fixture_name, test_suite_name, test_case_name, \
                             param)                                         \
    benchmarkFixture##_##test_suite_name##_##test_case_name                 \
        test_suite_name##_##test_case_name(stringify(test_suite_name),      \
                                           stringify(test_case_name), param)

#endif // BENCHMARKTEMPLATE_H
