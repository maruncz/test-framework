
set(TIMING_ENABLE_STD_CHRONO ON CACHE BOOL "")
set(TIMING_ENABLE_AVR OFF CACHE BOOL "")

configure_file(timingsettings.h.in ${CMAKE_CURRENT_BINARY_DIR}/timingsettings.h @ONLY)

set(ONLINESTATISTICS_SRCS
    onlinestatistic.h onlinestatistic.cpp
    )

set(TESTMANAGER_SRCS
    testmanager.h testmanager.cpp
    )

set(BASE_SRCS
    testabstract.h
    )

set(TESTS_SRCS
    testbase.h
    testcasebasic.h
    )

set(BENCHMARK_SRCS
    benchmarkbase.h
    benchmarkbasic.h
    benchmarksettings.h
    timing.h
    ${CMAKE_CURRENT_BINARY_DIR}/timingsettings.h
    )

add_library(test-fw-statistics STATIC ${ONLINESTATISTICS_SRCS})
target_include_directories(test-fw-statistics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(test-fw-testmanager STATIC ${TESTMANAGER_SRCS})
target_include_directories(test-fw-testmanager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(test-fw-base INTERFACE ${BASE_SRCS})
set_target_properties(test-fw-base PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(test-fw-base INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(test-fw-tests INTERFACE ${TESTS_SRCS})
set_target_properties(test-fw-tests PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(test-fw-tests INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(test-fw-benchmark INTERFACE ${BENCHMARK_SRCS})
set_target_properties(test-fw-benchmark PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(test-fw-benchmark INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test-fw-benchmark INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(test-fw-tests INTERFACE test-fw-base test-fw-testmanager)
target_link_libraries(test-fw-benchmark INTERFACE test-fw-base test-fw-testmanager test-fw-statistics)

add_library(test-fw-benchmark-main STATIC benchmark-main.cpp)
target_link_libraries(test-fw-benchmark-main PUBLIC test-fw-benchmark)

add_library(test-fw-tests-main STATIC test-main.cpp)
target_link_libraries(test-fw-tests-main PUBLIC test-fw-tests)
