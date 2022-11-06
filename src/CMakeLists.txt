
set(TIMING_OPTIONS AVR STD)
set(TIMING_BACKEND STD CACHE STRING "")
set_property(CACHE TIMING_BACKEND PROPERTY STRINGS ${TIMING_OPTIONS})

if(NOT TIMING_BACKEND IN_LIST TIMING_OPTIONS)
    message(FATAL_ERROR "TIMING_BACKEND must be one of ${TIMING_OPTIONS}")
endif()

if(${TIMING_BACKEND} STREQUAL AVR)
    set(TIMING_DEFINITION TIMING_ENABLE_AVR)
elseif(${TIMING_BACKEND} STREQUAL STD)
    set(TIMING_DEFINITION TIMING_ENABLE_STD_CHRONO)
endif()

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
    testmacros.h
)

set(TIMING_SRCS
    timing.h
    timing.cpp
)

set(BENCHMARK_SRCS
    benchmarkbase.h
    benchmarkbasic.h
    benchmarkfixture.h
    benchmarktemplate.h
    benchmarksettings.h
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
if(NOT MSVC)
    target_compile_options(test-fw-tests INTERFACE -Werror=return-type)
endif()

add_library(test-fw-timing STATIC ${TIMING_SRCS})
target_include_directories(test-fw-timing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(test-fw-timing PUBLIC ${TIMING_DEFINITION})

add_library(test-fw-benchmark STATIC ${BENCHMARK_SRCS})
set_target_properties(test-fw-benchmark PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(test-fw-benchmark INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test-fw-tests INTERFACE test-fw-base test-fw-testmanager)
target_link_libraries(test-fw-benchmark INTERFACE test-fw-base test-fw-testmanager test-fw-statistics test-fw-timing)

add_library(test-fw-benchmark-main STATIC benchmark-main.cpp)
target_link_libraries(test-fw-benchmark-main PUBLIC test-fw-benchmark)

add_library(test-fw-tests-main STATIC test-main.cpp)
target_link_libraries(test-fw-tests-main PUBLIC test-fw-tests)
