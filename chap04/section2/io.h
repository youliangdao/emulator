#ifndef __IO_H__
#define __IO_H__
#include <stdint.h>
uint8_t in_io8(uint16_t address);
void out_io8(uint16_t address, uint8_t value);

#endif