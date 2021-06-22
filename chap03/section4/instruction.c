#include <stdint.h>
#include "emulator.h"
#include "instruction.h"
#include "emulator_function.h"
#include "modrm.h"

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

//ModR/MのModとRMで指定される32bitのレジスタorメモリに32bitの即値を格納
static void mov_rm32_imm32(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t value = get_code32(emu, 0);
  emu->eip += 4;
  set_rm32(emu, &modrm, value);
}

//ModR/MのModとRMで指定される32bitのレジスタorメモリにREGで指定される32ビットのレジスタの値を格納
static void mov_rm32_r32(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t r32 = get_r32(emu, &modrm);
  set_rm32(emu, &modrm, r32);
}

//REGで指定される32ビットのレジスタの値にModR/MのModとRMで指定される32bitのレジスタorメモリの値を格納
static void mov_r32_rm32(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t rm32 = get_rm32(emu, &modrm);
  set_r32(emu, &modrm, rm32);
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
