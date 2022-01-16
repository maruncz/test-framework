
set(TEST_SRCS
    test_stats.cpp
    )

add_executable(test ${TEST_SRCS})
target_link_libraries(test PRIVATE gtest_main test-fw-statistics)
