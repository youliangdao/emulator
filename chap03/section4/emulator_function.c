#include "emulator_function.h"

//memory配列の指定した位置から8ビットの値を取得する
uint32_t get_code8(Emulator* emu, int index){
  return emu->memory[emu->eip + index];
}

//memory配列の指定した位置から符号付きで8ビットの値を取得する
int32_t get_sign_code8(Emulator* emu, int index){
  return (int8_t)emu->memory[emu->eip + index];
}

//memory配列の指定した位置から32ビットの値を取得する
uint32_t get_code32(Emulator* emu, int index){
  uint32_t ret;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_code8(emu, index + i) << (i * 8);
  }
  return ret;
}

//memory配列の指定した位置から32ビットの値を取得する
int32_t get_sign_code32(Emulator* emu, int index){
  return (int32_t)get_code32(emu, index);
}

//index番目の汎用レジスタに32bitの値を書き込む
void set_register32(Emulator* emu, int index, uint32_t value){
  emu->registers[index] = value;
}

//メモリのaddress番地に8bitの値を書き込む
void set_memory8(Emulator* emu, uint32_t address, uint32_t value){
  emu->memory[address] = value & 0xFF;
}

//メモリのaddress番地に32bitの値を書き込む
void set_memory32(Emulator* emu, uint32_t address, uint32_t value){
  for (int i = 0; i < 4; i++)
  {
    set_memory8(emu, address + i, value >> (8 * i));
  }

}

//index番目の32bit汎用レジスタの値を取得する
uint32_t get_register32(Emulator* emu, int index){
  return emu->registers[index];
}