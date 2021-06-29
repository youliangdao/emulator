#include "emulator_function.h"

// 指定されたプログラムカウンタから値を取得する
uint32_t get_code8(Emulator* emu, int index)
{
  return emu->memory[emu->eip + index];
}

// 指定されたプログラムカウンタから値を符号付きで取得する
int32_t get_sign_code8(Emulator* emu, int index)
{
  return (int8_t)emu->memory[emu->eip + index];
}

// 指定されたプログラムカウンタから4byte領域の値を取得する
uint32_t get_code32(Emulator* emu, int index)
{
  uint32_t ret = 0;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_code8(emu, index + i) << (8 * i);
  }

  return ret;
}

// 指定されたプログラムカウンタから4byte領域の値を符号付きで取得する
int32_t get_sign_code32(Emulator* emu, int index)
{
  return (int32_t)get_code32(emu, index);
}

//index番目の汎用レジスタに指定された32bit値を代入する
void set_register32(Emulator* emu, int index, uint32_t value)
{
  emu->registers[index] = value;
}

//指定アドレスに指定された32bit値の下位8bit値を格納する
void set_memory8(Emulator* emu, uint32_t value, uint32_t address)
{
  emu->memory[address] = value & 0xFF;
}

//指定アドレスから４byte領域に指定された32bit値を格納する
void set_memory32(Emulator* emu, uint32_t value, uint32_t address)
{
  for (int i = 0; i < 4; i++)
  {
    set_memory8(emu, value >> (8 * i), address + i);
  }
}

//index番目の汎用レジスタに格納されている32bit値を取得する
uint32_t get_register32(Emulator* emu, uint8_t index)
{
  return emu->registers[index];
}

//指定メモリアドレスから1byte値を取得する
uint8_t get_memory8(Emulator* emu, uint32_t address){
  return emu->memory[address];
}

//指定メモリアドレスから4byte値を取得する
uint32_t get_memory32(Emulator* emu, uint32_t address){
  uint32_t ret = 0;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_memory8(emu, address + i) << (8 * i);
  }

  return ret;
}

void set_carry(Emulator* emu, int is_carry)
{
  if (is_carry)
  {
    emu->eflags |= CARRY_FLAG;
  } else
  {
    emu->eflags &= ~CARRY_FLAG;
  }
}

void set_zero(Emulator* emu, int is_zero)
{
  if (is_zero)
  {
    emu->eflags |= ZERO_FLAG;
  } else
  {
    emu->eflags &= ~ZERO_FLAG;
  }
}

void set_sign(Emulator* emu, int is_sign)
{
  if (is_sign)
  {
    emu->eflags |= SIGN_FLAG;
  } else
  {
    emu->eflags &= ~SIGN_FLAG;
  }
}

void set_overflow(Emulator* emu, int is_overflow)
{
  if (is_overflow)
  {
    emu->eflags |= OVERFLOW_FLAG;
  } else
  {
    emu->eflags &= ~OVERFLOW_FLAG;
  }
}

int is_carry(Emulator* emu){
  return (emu->eflags & CARRY_FLAG) != 0;
}

int is_zero(Emulator* emu){
  return (emu->eflags & ZERO_FLAG) != 0;
}

int is_sign(Emulator* emu){
  return (emu->eflags & SIGN_FLAG) != 0;
}

int is_overflow(Emulator* emu){
  return (emu->eflags & OVERFLOW_FLAG) != 0;
}

void update_eflags_sub(Emulator* emu, uint32_t value1, uint32_t value2, uint64_t result)
{
  int sign1 = value1 >> 31;
  int sign2 = value2 >> 31;
  int signr = (result >> 31) & 1;
  set_carry(emu, result >> 32);
  set_sign(emu, signr);
  set_zero(emu, result == 0);
  set_overflow(emu, (sign1 != sign2) && (sign1 != signr));
}
