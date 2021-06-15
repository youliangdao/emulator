TARGET = List401.bin

ASM = nasm

.PHONY: all
all : $(TARGET)
	./$(TARGET)

%.bin: %.asm
	$(ASM) -f bin -o $@ $<

clean:
	rm -f $(TARGET)