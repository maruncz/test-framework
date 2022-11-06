#ifndef TIMING_H
#define TIMING_H

#include <cstdint>

#ifdef TIMING_ENABLE_STD_CHRONO
#include <chrono>

class timePoint : public std::chrono::steady_clock::time_point
{
public:
    explicit timePoint(const std::chrono::steady_clock::time_point &o)
        : std::chrono::steady_clock::time_point(o)
    {}
};

struct timing
{
    static timePoint now()
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

extern "C"
{
#include <avr/io.h>
}

#include <cstdio>

class timePoint
{
public:
    explicit timePoint(uint32_t inValue) : value(inValue) {}

private:
    uint32_t value{0};
    friend struct timing;
};

struct timing
{
    static void init();
    static timePoint now()
    {
        uint16_t ovf = overflowCount;
        uint32_t tcnt1 = TCNT1;
        uint32_t value = tcnt1;
        value += ovf * 65536;
        return timePoint(value);
    }
    static double duration(const timePoint &start, const timePoint &end)
    {
        uint32_t diff = 0;
        //overflow is sometimes missed
        if (end.value < start.value)
        {
            diff = end.value - start.value + 65536;
        }
        else
        {
            diff = end.value - start.value;
        }
        return static_cast<double>(diff) / F_CPU;
    }

    static volatile uint16_t overflowCount;
};

#endif

#endif // TIMING_H
