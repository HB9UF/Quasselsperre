#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "io.h"
#include "adc.h"

volatile uint16_t timer_seconds = 0;
static uint16_t tot_threshold = 0;

ISR(TIM0_COMPA_vect)
{
    if(!timer_expired()) timer_seconds++;
}

inline bool timer_expired(void)
{
    return timer_seconds > tot_threshold;
}

void timer_init(void)
{
    // Flash LED once for every 15 minutes of TOT time
    switch(adc_get_value())
    {
        case TOT_015_MIN:
            tot_threshold =  15*60;
            io_flash_led(1);
            break;
        case TOT_030_MIN:
            tot_threshold =  30*60;
            io_flash_led(2);
            break;
        case TOT_045_MIN:
            tot_threshold =  45*60;
            io_flash_led(3);
            break;
        case TOT_060_MIN:
            tot_threshold =  60*60;
            io_flash_led(4);
            break;
        case TOT_075_MIN:
            tot_threshold =  75*60;
            io_flash_led(5);
            break;
        case TOT_090_MIN:
            tot_threshold =  90*60;
            io_flash_led(6);
            break;
        case TOT_105_MIN:
            tot_threshold = 105*60;
            io_flash_led(7);
            break;
        case TOT_120_MIN:
            tot_threshold = 120*60;
            io_flash_led(8);
            break;
    }

    // CLK_io is 1 MHz. Dividing this by 1024 yields a period of 1.024 ms.
    // 977 of those periods are approx. 1 second, which is when we IRQ to
    // increment our seconds counter.
    TCCR0B |= (1 << WGM02); // Set CTC mode and 1024 prescaler

    const uint16_t ticks = 977;
    OCR0A = ticks;
    TIMSK0 |= (1 << OCIE0A);
    sei();
    timer_start();
}

void timer_start(void)
{
    TCCR0B |= (1 << CS02) | (1 << CS00); // 1024 prescaler
}

void timer_stop_and_reset(void)
{
    TCCR0B |= (0 << CS02) | (0 << CS00);
    timer_seconds = 0;
}
