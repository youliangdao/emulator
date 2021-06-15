#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

#define MEMORY_SIZE (1024 * 1024)

char* registers_name[] = {
  "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"
};

Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp)
{
  Emulator* emu = malloc(sizeof(Emulator));
  emu->memory = malloc(size);

  memset(emu->registers, 0, sizeof(emu->registers));
  emu->eip = eip;
  emu->registers[ESP] = esp;
  return emu;
}

void destroy_emu(Emulator* emu)
{
  free(emu->memory);
  free(emu);
}

void dump_registers(Emulator* emu)
{
  for (int i = 0; i < REGISTER_COUNT; i++)
  {
    printf("%s = %08x", registers_name[i], emu->registers[i]);
  }
  printf("EIP = %08x", emu->eip);
}

static void read_binary(Emulator* emu, const char* filename)
{
  FILE* binary;
  binary = fopen(filename, "rb");
  if (binary == NULL)
  {
    printf("%sファイルが開けません\n", filename);
    exit(1);
  }
  fread(emu->memory + 0x7c00, 1, 0x200, binary);
  fclose(binary);
}

int main(int argc, char const *argv[])
{
  Emulator* emu;

  if (argc != 2)
  {
    printf("usage: ./px86 filename\n");
    return 1;
  }

  init_instructions();

  emu = create_emu(sizeof(Emulator), 0x7c00, 0x7c00);

  read_binary(emu, argv[1]);

  while (emu->eip < MEMORY_SIZE)
  {
    uint8_t code = get_code8(emu, 0);

    printf("\n現在のプログラムカウンタと実行される機械語を出力します\nEIP = %08x, Code = %02x\n", emu->eip, code);

    if (instructions[code] == NULL)
    {
      printf("\n命令が実装されていません：%x\n", code);
      break;
    }

    instructions[code](emu);

    if (emu->eip == 0x00)
    {
      printf("\n\nプログラム終了\n\n");
      break;
    }
  }

  dump_registers(emu);
  destroy_emu(emu);
  return 0;
}