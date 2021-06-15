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

//メモリのindex番地の8bitの値を取得する
uint8_t get_memory8(Emulator* emu, uint32_t address){
  return emu->memory[address];
}

//メモリのindex番地の32bitの値を取得する
uint32_t get_memory32(Emulator* emu, uint32_t address){
  uint32_t ret;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_memory8(emu, address + i) << (8 * i);
  }
  return ret;
}

void push32(Emulator* emu, uint32_t value){
  uint32_t address = get_register32(emu, ESP) -4;
  set_register32(emu, ESP, address);
  set_memory32(emu, address, value);
}

uint32_t pop32(Emulator* emu){
  uint32_t address = get_register32(emu, ESP);
  uint32_t ret = get_memory32(emu, address);
  set_register32(emu, ESP, address + 4);
  return ret;
}

void set_carry(Emulator* emu, int is_carry){
  if (is_carry)
  {
    emu->eflgas |= CARRY_FLAG;
  }
  else
  {
    emu->eflgas &= ~CARRY_FLAG;
  }

}

void set_zero(Emulator* emu, int is_zero){
  if (is_zero)
  {
    emu->eflgas |= ZERO_FLAG;
  } else
  {
    emu->eflgas &= ~ZERO_FLAG;
  }

}

void set_sign(Emulator* emu, int is_sign){
  if (is_sign)
  {
    emu->eflgas |= SIGN_FLAG;
  }
  else
  {
    emu->eflgas &= ~SIGN_FLAG;
  }

}

void set_overflow(Emulator* emu, int is_overflow){
  if (is_overflow)
  {
    emu->eflgas |= OVERFLOW_FLAG;
  }
  else
  {
    emu->eflgas &= ~OVERFLOW_FLAG;
  }

}

int is_carry(Emulator* emu){
  return (emu->eflgas & CARRY_FLAG) != 0;
}

int is_zero(Emulator* emu){

}

int is_sign(Emulator* emu){
  return (emu->eflgas & SIGN_FLAG) != 0;
}

int is_overflow(Emulator* emu){

}

void update_eflags_sub(
  Emulator* emu, uint32_t v1, uint32_t v2, uint64_t result
)
{
  int sign1 = v1 >> 31;
  int sign2 = v2 >> 31;
  int signr = (result >> 31) & 1;

  set_carry(emu, result >> 32);
  set_zero(emu, result == 0);
  set_sign(emu, signr);
  set_overflow(emu, sign1 != sign2 && sign1 != signr);
}
