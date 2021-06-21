#include <stdio.h>
#include <stdint.h>

enum Register {EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT};

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

int main(void)
{
  Emulator* buf = (Emulator*)malloc(sizeof(Emulator) + 128);
  buf->eflgas = 1;
  buf->memory = buf + sizeof(Emulator);
  return 0;
}


