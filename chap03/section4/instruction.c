#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulator.h"
#include "instruction.h"
#include "emulator_function.h"
#include "modrm.h"

instruction_func_t* instructions[256];

void add_rm32_r32(Emulator* emu)
{
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  uint32_t rm32 = get_rm32(emu, &modrm);
  uint32_t r32 = get_register32(emu, modrm.reg_index);
  set_rm32(emu, &modrm, rm32 + r32);
}

void sub_rm32_imm8(Emulator* emu, ModRM* modrm)
{
  uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);
  uint32_t rm32 = get_rm32(emu, modrm);
  emu->eip += 1;

  set_rm32(emu, modrm, rm32 - imm8);
}


void code_83(Emulator* emu)
{
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  switch (modrm.opecode)
  {
  case 5:
    sub_rm32_imm8(emu, &modrm);
    break;

  default:
    printf("オペコード83の命令は実装されていません\n");
    exit(1);
  }
}

void mov_rm32_r32(Emulator* emu)
{
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  uint32_t value = emu->registers[modrm.reg_index];
  set_rm32(emu, &modrm, value);
}

void mov_r32_rm32(Emulator* emu)
{
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  set_register32(emu, modrm.reg_index, get_rm32(emu, &modrm));
}

void mov_rm32_imm32(Emulator* emu)
{
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t value = get_code32(emu, 0);
  emu->eip += 4;

  set_rm32(emu, &modrm, value);
}

void mov_r32_imm32(Emulator* emu)
{
  uint8_t reg = get_code8(emu, 0) - 0xB8;
  uint32_t value = get_code32(emu, 1);

  emu->registers[reg] = value;
  emu->eip += 5;
}

void near_jump(Emulator* emu)
{
  int32_t diff = get_sign_code32(emu, 1);
  emu->eip += (diff + 5);
}

void short_jump(Emulator* emu)
{
  int8_t diff = get_sign_code8(emu, 1);
  emu->eip += (diff + 2);
}


void init_instructions(void)
{
  memset(instructions, 0, sizeof(instructions));

  instructions[0x01] = add_rm32_r32;
  instructions[0x83] = code_83;
  instructions[0x89] = mov_rm32_r32;
  instructions[0x8B] = mov_r32_rm32;
  for (int i = 0; i < 8; i++)
  {
    instructions[0xB8 + i] = mov_r32_imm32;
  }
  instructions[0xC7] = mov_rm32_imm32;
  instructions[0xE9] = near_jump;
  instructions[0xEB] = short_jump;
}