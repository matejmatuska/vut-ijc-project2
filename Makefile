CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

.PHONY: all
all: tail

tail: tail.o

.PHONY:
pack:
	 zip xmatus36.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	-rm -f tail *.o

