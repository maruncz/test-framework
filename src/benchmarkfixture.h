#ifndef BENCHMARKFIXTURE_H
#define BENCHMARKFIXTURE_H

#include "benchmarkbase.h"

#define BENCHMARK_F(fixture_name, test_suite_name, test_case_name)         \
    class benchmarkFixture##_##test_suite_name##_##test_case_name          \
        : public fixture_name                                              \
    {                                                                      \
    public:                                                                \
        benchmarkFixture##_##test_suite_name##_##test_case_name(           \
            const std::string &inTestSuite, const std::string &inTestCase) \
            : fixture_name(inTestSuite, inTestCase)                        \
        {}                                                                 \
                                                                           \
        void runBenchmark() override;                                      \
    };                                                                     \
                                                                           \
    benchmarkFixture##_##test_suite_name##_##test_case_name                \
        test_suite_name##_##test_case_name(stringify(test_suite_name),     \
                                           stringify(test_case_name));     \
                                                                           \
    inline void                                                            \
        benchmarkFixture##_##test_suite_name##_##test_case_name::runBenchmark()

#endif // BENCHMARKFIXTURE_H
