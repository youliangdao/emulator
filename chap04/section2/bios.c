#include <stdio.h>
#include <stdint.h>

#include "bios.h"
#include "emulator_function.h"
#include "io.h"


static void bios_video_teletype(Emulator* emu)
{
    uint8_t code = get_register8(emu, AL);
    out_io8(0x03f8, code);
}

void bios_video(Emulator* emu)
{
    uint32_t func = get_register8(emu, AH);
    switch (func)
    {
    case 0x0e:
        bios_video_teletype(emu);
        break;

    default:
        printf("not implemented BIOS video function: 0x%02x\n", func);
    }
}