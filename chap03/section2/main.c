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
    printf("%s = %08x\n", registers_name[i], emu->registers[i]);
  }
  printf("EIP = %08x\n", emu->eip);
}

uint32_t get_code8(Emulator* emu, int index)
{
  return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator* emu, int index)
{
  return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator* emu, int index)
{
  uint32_t ret = 0;
  for (int i = 0; i < 4; i++)
  {
    ret |= get_code8(emu, index + i) << (8 * i);
  }

  return ret;
}

void mov_r32_imm32(Emulator* emu)
{
  uint8_t reg = get_code8(emu, 0) - 0xB8;
  uint32_t value = get_code32(emu, 1);

  emu->registers[reg] = value;
  emu->eip += 5;
}

void short_jump(Emulator* emu)
{
  int8_t diff = get_sign_code8(emu, 1);
  emu->eip += diff + 2;
}

//1バイト機械語に対応する関数のポインタを格納した関数ポインタテーブルを作成
typedef void instruction_func_t(Emulator*);
instruction_func_t* instructions[256];

void init_instructions(void)
{
  memset(instructions, 0, sizeof(instructions));
  for (int i = 0; i < 8; i++)
  {
    instructions[0xB8 + i] = mov_r32_imm32;
  }

  instructions[0xEB] = short_jump;

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


  init_instructions();

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
