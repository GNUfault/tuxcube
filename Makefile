CC      = gcc
SRC     = tuxcube.c
BIN     = tuxcube
OPT     = fast
MARCH   = native
MTUNE   = $(MARCH)
GDB     = 0
STD     = c99
FLAGS   = -Wall -Wextra -pedantic -pedantic-errors -pipe
LDFLAGS = -lm -ldl -lpthread -lGL -lX11
LDLIBS  = libraylib.a
CFLAGS  = -O$(OPT) -march=$(MARCH) -mtune=$(MTUNE) -g$(GDB) -std=$(STD) $(FLAGS)

all: compile strip

compile:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

strip:
	objcopy --strip-all $(BIN)

clean:
	rm -f $(BIN)
