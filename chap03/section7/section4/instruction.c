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

//REGで指定される32ビットのレジスタの値にModR/MのModとRMで指定される32bitのレジスタの値を格納
static void mov_r32_rm32(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t rm32 = get_rm32(emu, &modrm);
  set_r32(emu, &modrm, rm32);
}

//ModR/MのModとRMで指定される32bitのレジスタorメモリにREGで指定された32bitのレジスタの値を加算する
static void add_rm32_r32(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);
  uint32_t r32 = get_r32(emu, &modrm);
  uint32_t rm32 = get_rm32(emu, &modrm);
  set_rm32(emu, &modrm, r32 + rm32);
}

//ModR/MのModとRMで指定される32bitのレジスタorメモリに8bitの即値を減算する
static void sub_rm32_imm8(Emulator* emu, ModRM* modrm){
  uint32_t rm32 = get_rm32(emu, modrm);
  uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);
  emu->eip += 1;
  set_rm32(emu, modrm, rm32 - imm8);
}

static void code_83(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  switch (modrm.opecode)
  {
  case 5:
    sub_rm32_imm8(emu, &modrm);
    break;

  default:
    printf("not implemtend: 83 / %d\n");
    exit(1);
  }
}

//ModR/MのModとRMで指定される32bitのレジスタorメモリの値をインクリメントする
static void inc_rm32(Emulator* emu, ModRM* modrm){
  uint32_t value = get_rm32(emu, modrm);
  set_rm32(emu, modrm, value++);
}

static void code_ff(Emulator* emu){
  emu->eip += 1;
  ModRM modrm;
  parse_modrm(emu, &modrm);

  switch (modrm.opecode)
  {
  case 0:
    inc_rm32(emu, &modrm);
    break;

  default:
    printf("not implemented: FF / %d\n", modrm.opecode);
    exit(1);
  }
}

//push操作
static void push_r32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0x50;
  push32(emu, get_register32(emu, reg));
  emu->eip += 1;
}

//pop操作
static void pop_r32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0x58;
  set_register32(emu, reg, pop32(emu));
  emu->eip += 1;
}

//call命令
static void call_rel32(Emulator* emu){
  int32_t diff = get_sign_code32(emu, 1);
  push32(emu, emu->eip + 5);
  emu->eip += (diff + 5);
}

//ret命令
static void ret(Emulator* emu){
  emu->eip = pop32(emu);
}

//関数ポインタ型の配列instructionsの作成と初期化
//typedefを用いることにより関数ポインタ配列をわかりやすく記述している
void init_instrutions(void){
  int i;
  memset(instructions, 0, sizeof(instructions));
  instructions[0x01] = add_rm32_r32;

  for (i = 0; i < 8; i++)
  {
    instructions[0x50 + i] = push_r32;
  }

  for (i = 0; i < 0; i++)
  {
    instructions[0x58 + i] = pop_r32;
  }


  instructions[0x83] = code_83;
  instructions[0x89] = mov_rm32_r32;
  instructions[0x8B] = mov_r32_rm32;
  for (int i = 0; i < 8; i++)
  {
    instructions[0xB8 + i] = mov_r32_imm32;
  }

  instructions[0xC3] = ret;
  instructions[0xC7] = mov_rm32_imm32;

  instructions[0xE8] = call_rel32;
  instructions[0xEB] = short_jump;
  instructions[0xE9] = near_jump;
  instructions[0xFF] = code_ff;
}


