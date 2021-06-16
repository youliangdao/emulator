#ifndef __BIOS_H__
#define __BIOS_H__
#include "emulator.h"
#include <stdio.h>

void bios_video(Emulator* emu);
static void bios_video_teletype(Emulator* emu);
static void put_string(const char* s, size_t n);
#endif