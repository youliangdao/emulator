#ifndef __EMULATOR_FUNCTION_H__
#define __EMULATOR_FUNCTION_H__
#include <stdint.h>
#include "emulator.h"

//memory配列の指定した位置から8ビットの値を取得する
uint32_t get_code8(Emulator* emu, int index);

//memory配列の指定した位置から符号付きで8ビットの値を取得する
int32_t get_sign_code8(Emulator* emu, int index);

//memory配列の指定した位置から32ビットの値を取得する
uint32_t get_code32(Emulator* emu, int index);

//memory配列の指定した位置から32ビットの値を取得する
int32_t get_sign_code32(Emulator* emu, int index);

#endif