#ifndef TESTMACROS_H
#define TESTMACROS_H

#include <cmath>
#include <sstream>

#define ASSERT_NEAR(in1, in2, tol)                                      \
    do                                                                  \
    {                                                                   \
        if (std::abs((in1) - (in2)) > tol)                              \
        {                                                               \
            std::stringstream s;                                        \
            s << "Assertion failed: val1: " << in1 << " val2: " << in2; \
            return testBase::result{false, s.str()};                    \
        }                                                               \
    } while (0)

#endif // TESTMACROS_H
