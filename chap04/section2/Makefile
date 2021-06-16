TARGET = px86
PROGRAM = subroutine32.bin
OBJS = main.o emulator_function.o instruction.o modrm.o io.o bios.o

CC = gcc
ASM = nasm
CFLAGS += -Wall

.PHONY: all run
all: $(TARGET) $(PROGRAM)

run: $(TARGET) $(PROGRAM)
	./$(TARGET) -q $(PROGRAM)

%.bin: %.asm
	$(ASM) -f bin -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(TARGET) $(PROGRAM) $(OBJS)