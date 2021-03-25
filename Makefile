CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

all: tail

tail: tail.o

clean:
	-rm -f tail *.o

.PHONY: all clean
