#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE (1024 * 1024)

enum Register
{
  EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTER_COUNT
};

char* registers_name[] = {
  "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"
};

typedef struct
{
  uint32_t registers[REGISTER_COUNT];
  uint32_t eflags;
  uint8_t* memory;
  uint32_t eip;

} Emulator;


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

uint32_t get_code8(Emulator* emu, int index)
{
  return emu->memory[emu->eip + index];
}

//1バイト機械語に対応する関数のポインタを格納した関数ポインタテーブルを作成
typedef void instruction_func_t(Emulator*);
instruction_func_t* instructions[256];

void init_instructions(Emulator* emu)
{
  memset(instructions, 0, sizeof(instructions));
}


int main(int argc, char const *argv[])
{
  FILE* binary;
  Emulator* emu;

  if (argc != 2)
  {
    printf("usage: ./px86 filename\n");
    return 1;
  }


  binary = fopen(argv[1], "rb");
  emu = create_emu(sizeof(Emulator), 0x0000, 0x7c00);
  if (binary == NULL)
  {
    printf("%sファイルが開けません\n", argv[1]);
    exit(1);
  }
  fread(emu->memory, 1, 0x200, binary);
  fclose(binary);

  while (emu->eip < MEMORY_SIZE)
  {
    uint32_t code = get_code8(emu, 0);
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
