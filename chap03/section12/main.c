#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

//メモリは1MB（つまり、20バイトのメモリ空間を想定）
#define MEMORY_SIZE (1024 * 1024)

//Emulatorのメモリにバイナリファイルの内容を512バイト分コピーする
static void read_binary(Emulator* emu, const char* filename){
  FILE* binary;

  binary = fopen(filename, "rb");

  if (binary == NULL)
  {
    printf("%s　ファイルを開けません\n", filename);
    exit(1);
  }

  //Emulatorのメモリにバイナリファイルの内容を512バイトコピー
  fread(emu->memory + 0x7c00, 1, 512, binary);
  fclose(binary);

}

//汎用レジスタとプログラムカウントの値を標準出力へ出力する
static void dump_registers(Emulator* emu){
  for (int i = 0; i < REGISTERS_COUNT; i++)
  {
    printf("%s = %08x\n", register_name[i], get_register32(emu, i));
  }

  printf("EIP = %08x\n", get_register32(emu, emu->eip));
}

//与えられた引数を元にEmulatorを作成する
static Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp){

  //Emulatorの作成
  Emulator* emu = malloc(sizeof(Emulator));

  //Emulator内で使用するメモリ領域の確保
  emu->memory = malloc(size);

  //汎用レジスタを全て0にする
  memset(emu->registers, 0, sizeof(emu->registers));

  //プログラムカウンタとスタックポインタ の初期値設定
  emu->eip = eip;
  emu->registers[ESP] = esp;

  return emu;
}

static void destroy_emu(Emulator* emu){
  free(emu->memory);
  free(emu);
}

int opt_remove_at(int argc, char* argv[], int index){
  if (index < 0 || argc <= index)
  {
    return argc;
  }
  else
  {
    int i = index;

    for (; i < argc - 1; i++)
    {
      argv[i] = argv[i + 1];
    }
    argv[i] = NULL;
    return argc - 1;
  }
}

//メイン処理
int main(int argc, char* argv[])
{
  Emulator* emu;
  int quiet= 0;
  int i;

  i = 1;
  while (i < argc)
  {
    if (strcmp(argv[i], "-q") == 0)
    {
      quiet = 1;
      argc = opt_remove_at(argc, argv, i);
    }
    else
    {
      i++;
    }

  }


  if (argc != 2)
  {
    printf("usage: px86 filename\n");
    return 1;
  }

  //関数ポインタテーブルの作成
  init_instrutions();

  //EIPが0x7c00,ESPが0x7c00の状態のエミュレータを作る
  emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

  //引数で与えられたバイナリファイルを読み込む
  read_binary(emu, argv[1]);

  //命令の実行と終了
  while (emu->eip < MEMORY_SIZE)
  {
    uint8_t code = get_code8(emu, 0);

    //現在のプログラムカウントと実行されるバイナリを出力する
    if (!quiet)
    {
      /* code */
    }

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