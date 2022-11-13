#ifndef TESTMACROS_H
#define TESTMACROS_H

#include "testbase.h"
#include <cmath>
#include <sstream>

template<typename T>
testBase::result assert_near(T in1, T in2, T tol,
                             const std::string &msg = std::string())
{
    auto diff = std::abs((in1) - (in2));
    if (diff > tol)
    {
        std::stringstream ASSERT_NEAR_STRING;
        ASSERT_NEAR_STRING << "Assertion failed: val1: " << in1
                           << " val2: " << in2 << " diff: " << diff
                           << " tol: " << tol;
        if (!msg.empty())
        {
            ASSERT_NEAR_STRING << ", " << msg;
        }
        return testBase::result{false, ASSERT_NEAR_STRING.str()};
    }
    return testBase::result(true);
}

#define ASSERT_NEAR(in1, in2, tol) ASSERT_NEAR_MSG(in1, in2, tol, "")

#define ASSERT_NEAR_MSG(in1, in2, tol, msg)         \
    do                                              \
    {                                               \
        auto ret = assert_near(in1, in2, tol, msg); \
        if (!ret.getOk())                           \
        {                                           \
            return ret;                             \
        }                                           \
    } while (0)

#endif // TESTMACROS_H
