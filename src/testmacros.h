#ifndef TESTMACROS_H
#define TESTMACROS_H

#include <cmath>
#include <sstream>

#define ASSERT_NEAR(in1, in2, tol)                                      \
    do                                                                  \
    {                                                                   \
        auto diff = std::abs((in1) - (in2));                            \
        if (diff > tol)                                                 \
        {                                                               \
            std::stringstream ASSERT_NEAR_STRING;                       \
            ASSERT_NEAR_STRING << "Assertion failed: val1: " << in1     \
                               << " val2: " << in2 << " diff: " << diff \
                               << " tol: " << tol;                      \
            return testBase::result{false, ASSERT_NEAR_STRING.str()};   \
        }                                                               \
    } while (0)

#endif // TESTMACROS_H
