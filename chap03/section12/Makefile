TARGET = px86
PROGRAM = out.bin
OBJS = main.o emulator_function.o instruction.o modrm.o io.o

CC = gcc
LD = ld
ASM = nasm
CFLAGS += -Wall

.PHONY: all run
all: $(TARGET) $(PROGRAM)

run: $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

%.bin: %.asm
	$(ASM) -f bin -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(TARGET) $(PROGRAM) $(OBJS)