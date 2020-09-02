#ifndef _ADC_H
#define _ADC_H

#include <avr/io.h>

typedef enum {TOT_015_MIN, TOT_030_MIN, TOT_045_MIN, TOT_060_MIN, 
              TOT_075_MIN, TOT_090_MIN, TOT_105_MIN, TOT_120_MIN} adc_tot_time_t;
void adc_init(void);
adc_tot_time_t adc_get_value(void);

#endif
