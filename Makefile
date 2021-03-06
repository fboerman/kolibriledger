TARGET = kolibriledger
CC=gcc
CFLAGS = -g -Wall -std=gnu99 `pkg-config --cflags libsodium`
DEPS = 
LIBS = `pkg-config --libs libsodium`

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	rm *.o
	rm $(TARGET)
