#  Makefile

CC=gcc
SRC=4inarow.c move.c print.c dialogue.c
CFLAGS=-Wall
LDFLAGS=-lncurses
TARGET=4inarow

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	$(RM) $(TARGET)

.PHONY: all clean
