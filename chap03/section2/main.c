#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE (1024 * 1024);

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

int main(int argc, char const *argv[])
{
  Emulator* emu = create_emu(sizeof(Emulator), 0x0000, 0x7c00);
  destroy_emu(emu);
  return 0;
}
