#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"

#include "modrm.h"
#include "io.h"

uint8_t in_io8(uint16_t address)
{
  switch (address)
  {
  case 0x3f8:
    return getchar();

  default:
    return 0;
  }
}

void out_io8(uint16_t address, uint8_t value)
{

}