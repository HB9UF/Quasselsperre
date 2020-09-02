#ifndef _IO_H
#define _IO_H

#include <stdint.h>
#include <stdbool.h>

void io_init(void);
void io_set_led(void);
void io_clear_led(void);
void io_flash_led(uint8_t n);
void io_set_ptt(void);
void io_clear_ptt(void);
bool io_get_ptt(void);

#endif
