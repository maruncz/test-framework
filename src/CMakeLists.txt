
set(SRCS
    onlinestatistic.h onlinestatistic.cpp
    testbase.h
    testcasebasic.h
    testmanager.h testmanager.cpp
    )

add_library(test-fw STATIC ${SRCS})
target_include_directories(test-fw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
