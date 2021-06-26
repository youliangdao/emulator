#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#include <stdint.h>

enum Register
{
  EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTER_COUNT
};

typedef struct
{
  uint32_t registers[REGISTER_COUNT];
  uint32_t eflags;
  uint8_t* memory;
  uint32_t eip;
} Emulator;

#endif