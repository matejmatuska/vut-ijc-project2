CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

.PHONY: all
all: tail

tail: tail.o

wordcount: wordcount.o libhtab.a
	gcc $< -L. -o $@ -lhtab

libhtab.a: htab_init.o htab_size.o htab_bucket_count.o
	ar rcs $@ $<

libhtab.so: htab_size.o htab_bucket_count.o

htab_init.o: htab_init.c htab.h htab_internal.h
htab_size.o: htab_size.c htab.h htab_internal.h
htab_bucket_count.o: htab_bucket_count.c htab.h htab_internal.h

.PHONY: pack
pack:
	 zip xmatus36.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	-rm -f tail *.o

