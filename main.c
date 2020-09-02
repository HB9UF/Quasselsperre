#include "config.h"
#include <util/delay.h>
#include <avr/io.h>

#include "io.h"
#include "adc.h"
#include "timer.h"

int main(void)
{
    io_init();
    adc_init();
    timer_init();
    while(1)
    {
        // FIXME: Investigate if we can sleep here to save power instead of running a busy-wait.
        _delay_ms(1000);
        if(timer_expired())
        {
            io_clear_ptt();
            if(io_get_ptt())
            {
                io_flash_led(1);
            }
        }
    }
    return 0;
}
