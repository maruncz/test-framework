
set(TEST_SRCS
    test_stats.cpp
    )

foreach(test ${TEST_SRCS})
    get_filename_component(TName ${test} NAME_WE)
    add_executable(${TName} ${test})
    target_link_libraries(${TName} PRIVATE test-fw-tests-main)
    add_test(NAME ${TName} COMMAND ${TName})
endforeach()


target_link_libraries(test_stats PRIVATE test-fw-statistics)
