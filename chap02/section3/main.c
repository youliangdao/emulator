#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//メモリは1MB
#define MEMORY_SIZE (1024 * 1024)

enum Register {EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT};

//文字列の配列
char* register_name[] = {
    "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"
};

typedef struct
{
  //汎用レジスタ
  uint32_t registers[REGISTERS_COUNT];

  //EFLAGSレジスタ
  uint32_t eflgas;

  //メモリ（バイト列）
  uint8_t* memory;

  //プログラムカウンタ
  uint32_t eip;

} Emulator;

//エミュレータを作成する
Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp)
{
  Emulator* emu = malloc(sizeof(Emulator));
  emu->memory = malloc(size);

  //汎用レジスタの初期値を全て0にする
  memset(emu->registers, 0, sizeof(Emulator));

  //レジスタの初期値を指定されたものにする
  emu->eip = eip;
  emu->registers[ESP] = esp;

  return emu;
}

//エミュレータを破棄する
void destroy_emu(Emulator* emu){
  free(emu->memory);
  free(emu);
}

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

  //EIPが0,ESPが0x7c00の状態のエミュレータを作る
  emu = create_emu(MEMORY_SIZE, 0x0000, 0x7c00);

  //読み取り専用でオープン
  if (fp = fopen(argv[1], "rb") == NULL)
  {
    printf("%sファイルが開けません\n", argv[1]);
    exit(1);
  }

  //機械語ファイルを読み込む(最大512バイト)
  fread(emu->memory, 1, 0x200, fp);
  fclose(fp);

  destroy_emu(emu);
  return 0;
}

