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

//index番目の32bit汎用レジスタに値を設定する
void set_register32(Emulator* emu, int index, uint32_t value);

//メモリのaddress番地に8bit値を設定する
void set_memory8(Emulator* emu, uint32_t address, uint32_t value);

//メモリのaddress番地に32bit値を設定する
void set_memory32(Emulator* emu, uint32_t address, uint32_t value);

//index番目の32bit汎用レジスタの値を取得する
uint32_t get_register32(Emulator* emu, int index);

#endif