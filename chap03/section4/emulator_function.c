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
