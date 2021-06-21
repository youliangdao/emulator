#include <stdint.h>
#include "emulator.h"
#include "instruction.h"
#include "emulator_function.h"

//汎用レジスタに32ビットのリテラルをコピーするmov命令のエミュレート
void mov_r32_imm32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0xB8;
  uint32_t value = get_code32(emu, 1);
  emu->registers[reg] = value;
  emu->eip += 5;
}

//1バイトのメモリ番地を取るjmp命令のエミュレート
void short_jump(Emulator* emu){
  int8_t diff =  get_sign_code8(emu, 1);
  emu->eip += (diff + 2);
}

//１バイトのメモリ番地を取るjmp命令のエミュレート（より広い範囲に対応できるように）
void near_jump(Emulator* emu){
  int32_t diff = get_code32(emu, 1);
  emu->eip += (diff + 5);
}

//関数ポインタ型の配列instructionsの作成と初期化
//typedefを用いることにより関数ポインタ配列をわかりやすく記述している
void init_instrutions(void){
  int i;
  memset(instructions, 0, sizeof(instructions));
  for (int i = 0; i < 8; i++)
  {
    instructions[0xB8 + i] = mov_r32_imm32;
  }
  instructions[0xEB] = short_jump;
  instructions[0xe9] = near_jump;
}