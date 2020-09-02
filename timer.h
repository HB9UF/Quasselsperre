#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include <stdbool.h>

void timer_init(void);
bool timer_expired(void);
void timer_start(void);
void timer_stop_and_reset(void);

#endif
