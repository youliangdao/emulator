#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "emulator.h"

//関数ポインタテーブルの初期化関数の宣言
void init_instructions(void);

//関数ポインタテーブルの定義
typedef void instruction_func_t(Emulator*);
extern instruction_func_t* instructions[256];

#endif