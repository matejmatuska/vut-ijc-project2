# Makefile
# Řešení IJC-DU2 15.4.2021
# Autor: Matej Matuška, FIT
# Přeloženo: gcc 10.2.1

CFLAGS = -std=c99 -Wall -Wextra -pedantic -fPIC #-DHASHTEST #-DMOVETEST

BIN = tail wordcount wordcount-dynamic
HTAB_OBJS = htab_hash_func.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o \
			htab_lookup_add.o htab_for_each.o htab_erase.o htab_clear.o htab_free.o htab_move.o

.PHONY: all
all: $(BIN)

tail: tail.o

wordcount: wordcount.o io.o libhtab.a
	$(CC) -o $@ -static wordcount.o io.o -L. -lhtab

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) -o $@ wordcount.o io.o -L. -lhtab

libhtab.a: $(HTAB_OBJS)
	$(AR) rcs $@ $^

libhtab.so: $(HTAB_OBJS)
	$(LD) -shared -fPIC $^ -o $@

io.o: io.c io.h

htab_%.o: htab_%.c htab.h htab_internal.h

.PHONY: pack
pack:
	 zip xmatus36.zip *.c *.h Makefile

.PHONY: clean
clean:
	$(RM) *.o $(BIN)
