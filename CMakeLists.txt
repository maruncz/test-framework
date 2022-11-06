cmake_minimum_required(VERSION 3.11)

project(test-framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TEST_FW_BUILD_TESTS "")
option(TEST_FW_BUILD_DEV_BINARIES "")

add_subdirectory(src)

if(${TEST_FW_BUILD_TESTS})
    add_subdirectory(tests)
endif()

if(${TEST_FW_BUILD_DEV_BINARIES})
    set(SRCS
        main.cpp
        test.cpp)

    add_executable(benchmark-test ${SRCS})
    target_link_libraries(benchmark-test PRIVATE test-fw-tests test-fw-benchmark)
endif()
