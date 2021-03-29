CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

.PHONY: all
all: tail libhtab.a wordcount

tail: tail.o

wordcount: wordcount.o libhtab.a
	gcc $< -L. -o $@ -lhtab

libhtab.a: htab_hash_func.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_for_each.o
	ar rcs $@ $^

htab_init.o: htab_init.c htab.h htab_internal.h
htab_size.o: htab_size.c htab.h htab_internal.h
htab_bucket_count.o: htab_bucket_count.c htab.h htab_internal.h
htab_find.o: htab_find.c htab.h htab_internal.h
htab_lookup_add.o: htab_lookup_add.c htab.h htab_internal.h
htab_for_each.o: htab_for_each.c htab.h htab_internal.h

.PHONY: pack
pack:
	 zip xmatus36.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	-rm -f *.o tail wordcount

