cmake_minimum_required(VERSION 3.5)

project(benchmark-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    onlinestatistic.h onlinestatistic.cpp
    main.cpp)

add_executable(benchmark-test ${SRCS})
