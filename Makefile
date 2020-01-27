#  Makefile

CC=gcc
SRC=4inarow.c move.c print.c dialogue.c
CFLAGS=-Wall
LDFLAGS=-lncurses
OBJECTS=$(SRC:.c=.o)
TARGET=4inarow

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

.PHONY: all
all: $(TARGET)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(TARGET)

