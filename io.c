#include "config.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.h"
#include "timer.h"

ISR(INT0_vect)
{
    if(io_get_ptt())
    {
        io_set_ptt();
        io_set_led();
        timer_start();
    }
    else
    {
        io_clear_ptt();
        io_clear_led();
        timer_stop_and_reset();
    }
}

void io_init(void)
{
    // PB0 is output to LED, PB1 is PTT output to radio
    io_clear_led();
    io_clear_ptt();
    DDRB |= (1 << DDB0) | (1 << DDB1);

    // PB2/INT0 is PTT input from raspberry pi, interrupt-driven
    EICRA = 1; // Any logical change on INT0 generates IRQ
    EIMSK = 1; // Enable external pin interrupt
    sei();
}

void io_set_led(void)
{
    // LED is active low
    PORTB &= ~(1 << PORTB0);
}

void io_clear_led(void)
{
    PORTB |= (1 << PORTB0);
}

void io_flash_led(uint8_t n)
{
    for(uint8_t i=0; i<n; i++)
    {
        io_set_led();
        _delay_ms(100);
        io_clear_led();
        _delay_ms(400);
    }
}

void io_set_ptt(void)
{
    // PTT is active high
    PORTB |= (1 << PORTB1);
}

void io_clear_ptt(void)
{
    PORTB &= ~(1 << PORTB1);
}

inline bool io_get_ptt(void)
{
    return PINB & (1 << PINB2);
}
