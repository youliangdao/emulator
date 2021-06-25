TARGET = a.out

CC = gcc

.PHONY: all
all: $(TARGET)
	./$(TARGET)

$(TARGET): sample.c
	$(CC) $<

clean:
	rm -f $(TARGET)