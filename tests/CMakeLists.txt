
set(TEST_SRCS
    test_stats.cpp
    )

add_executable(test ${TEST_SRCS})
target_link_libraries(test PRIVATE test-fw-statistics test-fw-tests-main)
