#ifndef BENCHMARKBASIC_H
#define BENCHMARKBASIC_H

#include "benchmarkbase.h"

#define BENCHMARK(test_suite_name, test_case_name)                         \
    class benchmarkBasic##_##test_suite_name##_##test_case_name            \
        : public benchmarkBase                                             \
    {                                                                      \
    public:                                                                \
        benchmarkBasic##_##test_suite_name##_##test_case_name(             \
            const std::string &inTestSuite, const std::string &inTestCase) \
            : benchmarkBase(inTestSuite, inTestCase)                       \
        {}                                                                 \
                                                                           \
        void runBenchmark() override;                                      \
    };                                                                     \
                                                                           \
    benchmarkBasic##_##test_suite_name##_##test_case_name                  \
        test_suite_name##_##test_case_name(stringify(test_suite_name),     \
                                           stringify(test_case_name));     \
                                                                           \
    inline void                                                            \
        benchmarkBasic##_##test_suite_name##_##test_case_name::runBenchmark()

#endif // BENCHMARKBASIC_H
