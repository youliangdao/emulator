#include <stdint.h>
#include <stdlib.h>
#include "emulator.h"

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