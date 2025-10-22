CC = gcc
CFLAGS = -Wall -lm
SRC = $(wildcard src/*.c)
TARGET = synth

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.wav

.PHONY: all run clean
