#include "emulator.h"
#include "modrm.h"
#include "emulator_function.h"

void parse_modrm(Emulator* emu, ModRM* modrm){
  uint8_t code;
  //全部を0に初期化
  memset(modrm, 0, sizeof(ModRM));

  //ModR/Mバイトの各ビットを取り出してmod,opecode,rmに書き込む
  code = get_code8(emu, 0);
  modrm->mod = ((code & 0xc0) >> 6);
  modrm->opecode = ((code & 0x38) >> 3);
  modrm->rm = code & 0x07;

  //プログラムカウンタを1バイト分進める
  emu->eip += 1;

  //SIBの存在条件を判定し、存在するなら読み取ってsibに書き込む
  if (modrm->mod != 3 && modrm->rm == 4)
  {
    modrm->sib = get_code8(emu,0);
    emu->eip += 1;
  }

  //ディスプレートメントの有無を判定し、ビット幅に応じて書き込む
  if ((modrm->mod == 3 && modrm->rm == 5) || modrm->mod == 2)
  {
    modrm->disp32 = get_sign_code32(emu, 0);
    emu->eip += 4;
  } else if (modrm->mod == 1)
  {
    modrm->disp8 = get_sign_code8(emu, 0);
    emu->eip += 1;
  }
}