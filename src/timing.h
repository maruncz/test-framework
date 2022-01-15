#ifndef TIMING_H
#define TIMING_H

#include <cstdint>
#include <timingsettings.h>

#ifdef TIMING_ENABLE_STD_CHRONO
#    include <chrono>

class timePoint : public std::chrono::steady_clock::time_point
{
public:
    explicit timePoint(const std::chrono::steady_clock::time_point &o)
        : std::chrono::steady_clock::time_point(o)
    {
    }

    static timePoint now() noexcept
    {
        return timePoint(std::chrono::steady_clock::now());
    }

    static double duration(const timePoint &start, const timePoint &end)
    {
        return std::chrono::duration<double>(end - start).count();
    }
};

#endif

#ifdef TIMING_ENABLE_AVR
class timePoint
{
public:
    static timePoint now() {}

    static double duration(const timePoint &start, const timePoint &end) {}

private:
    timePoint operator-(const timePoint &o) {}

    static constexpr double overflowPeriod{1};
    uint64_t value{0};
};
#endif

#endif // TIMING_H
