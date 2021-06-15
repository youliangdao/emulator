TARGET = px86
PROGRAM = separation.bin
OBJS = main.o emnulator_function.o instruction.o

CC = gcc
ASM = nasm
CFLAGS += -Wall

.PHONY: all run
all: $(TARGET)

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