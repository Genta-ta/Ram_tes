CC ?= gcc
CFLAGS += -O3 -Wall -Iinclude

SRC = src/main.c src/ram.c src/storage.c
TARGET = systest

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean

