#ifndef __EMULATOR_H__
#define __EMULATOR_H__
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

#endif