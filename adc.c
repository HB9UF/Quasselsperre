#include "adc.h"

void adc_init(void)
{
    DIDR0 = (1 << ADC3D);   // Disable digital input for PB3/ADC3 pin
    ADMUX = 0b11;           // Select PB3/ADC3 analog channel
    ADCSRA |= (1 << ADEN);  // Enable ADC
}

adc_tot_time_t adc_get_value(void)
{
    const uint8_t INC = 256/8;  // 8-bit ADC;adc_tot_time_t has 8 entries
    PRR &= ~(1 << PRADC);       // Wake up ADC if needed
    ADCSRA |= (1 << ADSC);      // Start conversion
    while (ADCSRA & (1<<ADSC)); // Wait

    const uint8_t result = ADCL;
    // Be tidy and disable ADC after conversion
    PRR |= (1 << PRADC);

    if(result < 1*INC) return TOT_015_MIN;
    if(result < 2*INC) return TOT_030_MIN;
    if(result < 3*INC) return TOT_045_MIN;
    if(result < 4*INC) return TOT_060_MIN;
    if(result < 5*INC) return TOT_075_MIN;
    if(result < 6*INC) return TOT_090_MIN;
    if(result < 7*INC) return TOT_105_MIN;
                       return TOT_120_MIN;
}
