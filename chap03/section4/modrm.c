#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"
#include "modrm.h"

/* この関数を呼び出す際は、プログラムカウンタはModR/Mバイトを指している状態で
必要がある */
void parse_modrm(Emulator* emu, ModRM* modrm)
{
  uint8_t code;

  memset(modrm, 0, sizeof(ModRM));  //全部を0に初期化

  //mod, opecode(reg_index), rmを格納
  code = get_code8(emu, 0);
  modrm->mod = ((code & 0xC0) >> 6);
  modrm->opecode = ((code & 0x38) >> 3);
  modrm->rm = (code & 0x07);

  //sib格納
  emu->eip += 1;

  if (modrm->mod != 3 && modrm->rm == 0x04)
  {
    modrm->sib = get_code8(emu, 0);
    emu->eip += 1;
  }

  //disp8もしくはdisp32を格納
  if (modrm->mod == 0x02)
  {
    modrm->disp32 = get_code32(emu, 0);
    emu->eip += 4;
  }
  else if (modrm->mod == 0x01)
  {
    modrm->disp8 = get_code8(emu, 0);
    emu->eip += 1;
  }
  else if (modrm->mod == 0x00 && modrm->rm == 0x05)
  {
    modrm->disp32 = get_code32(emu, 0);
    emu->eip += 4;
  }
}

/* ModRMで指定したレジスタもしくはメモリアドレスに32bitの値を格納する */
void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value)
{
  if (modrm->mod == 0x03)
  {
    set_register32(emu, modrm->rm, value);
  } else
  {
    uint32_t address = calc_memory_address(emu, modrm);
    set_memory32(emu, value, address);
  }
}

/* ModRMとディスプレースメントの値からメモリアドレスを計算する */
uint32_t calc_memory_address(Emulator* emu, ModRM* modrm)
{
  uint32_t ret = 0;
  if (modrm->rm != 0x04 && modrm->mod == 0x01)
  {
    ret = emu->registers[modrm->rm] + modrm->disp8;
    return ret;
  } else if (modrm->rm != 0x04 && modrm->mod == 0x02)
  {
    ret = emu->registers[modrm->rm] + modrm->disp32;
    return ret;
  }else if (modrm->rm != 0x04 && modrm->rm == 0x05 && modrm->mod == 0x00)
  {
    ret = emu->memory[modrm->disp8];
    return ret;
  } else if (modrm->rm != 0x04 && modrm->rm != 0x05 && modrm->mod == 0x00)
  {
    ret = emu->registers[modrm->rm];
    return ret;
  }
}
