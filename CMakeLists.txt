cmake_minimum_required(VERSION 3.11)

project(test-framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



option(TEST_FW_BUILD_TESTS "")
option(TEST_FW_BUILD_DEV_BINARIES "")

add_subdirectory(src)

if(${TEST_FW_BUILD_TESTS})
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
        )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests)
endif()
if(${TEST_FW_BUILD_DEV_BINARIES})
    set(SRCS
        main.cpp
        test.cpp)

    add_executable(benchmark-test ${SRCS})
    target_link_libraries(benchmark-test PRIVATE test-fw-tests test-fw-benchmark)
endif()
