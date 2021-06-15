#include <stdio.h>
#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

//メイン処理
int main(int argc, char const *argv[])
{
  FILE* fp;
  Emulator* emu;

  if (argc != 2)
  {
    printf("usage: px86 filename\n");
    return 1;
  }

  //EIPが0x7c00,ESPが0x7c00の状態のエミュレータを作る
  emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

  //読み取り専用でオープン
  if (fp = fopen(argv[1], "rb") == NULL)
  {
    printf("%sファイルが開けません\n", argv[1]);
    exit(1);
  }

  //機械語ファイルを読み込む(最大512バイト)
  fread(emu->memory + 0x7c00, 1, 0x200, fp);
  fclose(fp);

  //関数ポインタテーブルの作成
  init_instrutions();

  //命令の実行と終了
  while (emu->eip < MEMORY_SIZE)
  {
    uint8_t code = get_code8(emu, 0);

    //現在のプログラムカウントと実行されるバイナリを出力する
    printf("EIP = 0x%08X, Code = %02X\n", emu->eip, code);

    if (instructions[code] == NULL)
    {
      printf("\n\nNot Implemented: %x\n", code);
      break;
    }

    //命令の実行
    instructions[code](emu);

    //
    if (emu->eip == 0)
    {
      printf("\n\nEnd of program. \n\n");
      break;
    }
  }

  dump_registers(emu);
  destroy_emu(emu);
  return 0;
}