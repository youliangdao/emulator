TARGET = px86
PROGRAM = helloworld.bin
OBJS = main.o

CC = gcc
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run
all : $(TARGET)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) %(PROGRAM)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.bin : %.asm
	nasm -f bin -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM)





