#include <stdint.h>
#include <stdlib.h>
#include "emulator.h"

uint32_t get_code8(Emulator* emu, int index)
{
  return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator* emu, int index)
{
  return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator* emu, int index)
{
  uint32_t ret = 0;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_code8(emu, index + i) << (8 * i);
  }

  return ret;
}

int32_t get_sign_code32(Emulator* emu, int index)
{
  return (int32_t)get_code32(emu, index);
}

void set_register32(Emulator* emu, int index, uint32_t value)
{
  emu->registers[index] = value;
}

void set_memory32(Emulator* emu, uint32_t value, uint32_t address)
{
  uint8_t ret = 0;
  for (int i = 0; i < 4; i++)
  {
    ret |= value >> (8 * i);
    emu->memory[address + i] = ret;
  }
}