#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "emulator.h"

void init_instructions(void);

//1バイト機械語に対応する関数のポインタを格納した関数ポインタテーブルを作成
typedef void instruction_func_t(Emulator*);

extern instruction_func_t* instructions[256];

#endif