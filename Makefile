#  Makefile

CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncurses

.PHONY: all
all: 4inarow

.PHONY: clean
clean:
	$(RM) *~ *.o 4inarow

OBJECTS=4inarow.o
4inarow: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o 4inarow $(LDFLAGS)
