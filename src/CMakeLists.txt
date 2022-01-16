

set(TIMING_ENABLE_STD_CHRONO ON CACHE BOOL "")
set(TIMING_ENABLE_AVR OFF CACHE BOOL "")

configure_file(timingsettings.h.in ${CMAKE_CURRENT_BINARY_DIR}/timingsettings.h @ONLY)

set(SRCS
    onlinestatistic.h onlinestatistic.cpp
    testabstract.h
    testbase.h
    testcasebasic.h
    testmanager.h testmanager.cpp
    benchmarkbase.h
    benchmarkbasic.h
    timing.h
    benchmarksettings.h
    ${CMAKE_CURRENT_BINARY_DIR}/timingsettings.h
    )

add_library(test-fw STATIC ${SRCS})
target_include_directories(test-fw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test-fw PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
