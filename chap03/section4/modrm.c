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

/* ModRMで指定したレジスタもしくはメモリアドレスから32bitの値を取得する */
uint32_t get_rm32(Emulator* emu, ModRM* modrm)
{
  if (modrm->mod == 0x03)
  {
    return get_register32(emu, modrm->rm);
  } else
  {
    uint32_t address = calc_memory_address(emu, modrm);
    return get_memory32(emu, address);
  }
}

/* ModRMとディスプレースメントの値からメモリアドレスを計算する */
uint32_t calc_memory_address(Emulator* emu, ModRM* modrm)
{
  if (modrm->mod == 0)
  {
    if (modrm->rm == 4)
    {
      printf("ModRM mod = 0 rm = 4 はSIBを用いるため、ここでは実装されていません\n");
      exit(0);
    } else if (modrm->rm == 5)
    {
      return modrm->disp32;
    } else
    {
      return get_register32(emu, modrm->rm);
    }

  }
  else if (modrm->mod == 1)
  {
    if (modrm->rm == 4)
    {
      printf("ModRM mod = 1 rm = 4 はSIBを用いるため、ここでは実装されていません\n");
      exit(0);
    } else
    {
      return get_register32(emu, modrm->rm) + modrm->disp8;
    }
  }
  else if (modrm->mod == 2)
  {
    if (modrm->rm == 4)
    {
      printf("ModRM mod = 2 rm = 4 はSIBを用いるため、ここでは実装されていません\n");
      exit(0);
    } else
    {
      return get_register32(emu, modrm->rm) + modrm->disp32;
    }
  }
  else
  {
    printf("ModRM mod =3 はメモリアドレスではなくレジスタを示すため実装されていません\n");
    exit(0);
  }
}
