#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

uint8_t io_in8(uint16_t address);
void io_out8(uint16_t address, uint8_t value);

#endif