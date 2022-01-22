#include "timing.h"

#ifdef TIMING_ENABLE_AVR
extern "C"
{
#    include <avr/interrupt.h>
}

ISR(TIMER1_OVF_vect)
{
    ++timing::overflowCount;
}

void timing::init()
{
    overflowCount = 0;
    // Set timer 1 to count cycles
    TCCR1B = 1;
    TIMSK |= (1 << TOIE1);
    sei();
}

volatile uint16_t timing::overflowCount = 0;

#endif
