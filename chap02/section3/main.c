#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//メモリは1MB（つまり、20バイトのメモリ空間を想定）
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

//memory配列の指定した位置から8ビットの値を取得する
uint32_t get_code8(Emulator* emu, int index){
  return emu->memory[emu->eip + index];
}

//memory配列の指定した位置から符号付きで8ビットの値を取得する
int32_t get_sign_code8(Emulator* emu, int index){
  return (int8_t)emu->memory[emu->eip + index];
}

//memory配列の指定した位置から32ビットの値を取得する
uint32_t get_code32(Emulator* emu, int index){
  uint32_t ret;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_code8(emu, index + i) << (i * 8);
  }
  return ret;
}


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

//関数ポインタテーブルの作成
typedef void instruction_func_t(Emulator*);

  //関数ポインタ型の配列instructionsの作成と初期化
instruction_func_t* instructions[256];
void init_instrutions(void){
  memset(instructions, 0, sizeof(instructions));
  for (int i = 0; i < 8; i++)
  {
    instructions[0xB8 + i] = mov_r32_imm32;
  }
  instructions[0xEB] = short_jump;
}

//汎用レジスタとプログラムカウンタの値を出力
void dump_registers(Emulator* emu){
  for (int i = 0; i < REGISTERS_COUNT; i++)
  {
    printf("%s = %08x\n", register_name[i], emu->registers[i]);
  }

  printf("EIP = %08x\n", emu->eip);
}

//メイン処理
int main(int argc, char const *argv[])
{
  FILE* binary;
  Emulator* emu;

  if (argc != 2)
  {
    printf("usage: px86 filename\n");
    return 1;
  }

  //EIPが0,ESPが0x7c00の状態のエミュレータを作る
  emu = create_emu(MEMORY_SIZE, 0x0000, 0x7c00);

  //読み取り専用でオープン
  binary = fopen(argv[1], "rb");
  if (binary == NULL)
  {
    printf("%sファイルが開けません\n", argv[1]);
    exit(1);
  }

  //機械語ファイルを読み込む(最大512バイト)
  fread(emu->memory, 1, 0x200, binary);
  fclose(binary);

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

