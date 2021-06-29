#ifndef __EMULATOR_FUNCTION_H__
#define __EMULATOR_FUNCTION_H__

#define CARRY_FLAG (1)
#define ZERO_FLAG (1 << 6)
#define SIGN_FLAG (1 << 7)
#define OVERFLOW_FLAG (1 << 11)

#include <stdint.h>

#include "emulator.h"

uint32_t get_code8(Emulator* emu, int index);
int32_t get_sign_code8(Emulator* emu, int index);
uint32_t get_code32(Emulator* emu, int index);
int32_t get_sign_code32(Emulator* emu, int index);
void set_register32(Emulator* emu, int index, uint32_t value);
void set_memory8(Emulator* emu, uint32_t value, uint32_t address);
void set_memory32(Emulator* emu, uint32_t value, uint32_t address);
uint32_t get_register32(Emulator* emu, uint8_t index);
uint8_t get_memory8(Emulator* emu, uint32_t address);
uint32_t get_memory32(Emulator* emu, uint32_t address);
void set_carry(Emulator* emu, int is_carry);
void set_zero(Emulator* emu, int is_zero);
void set_sign(Emulator* emu, int is_sign);
void set_overflow(Emulator* emu, int is_overflow);
int is_carry(Emulator* emu);
int is_zero(Emulator* emu);
int is_sign(Emulator* emu);
int is_overflow(Emulator* emu);

void update_eflags_sub(Emulator* emu, uint32_t value1, uint32_t value2, uint64_t result);
#endif