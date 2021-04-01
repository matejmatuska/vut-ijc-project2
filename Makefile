CFLAGS= -std=c99 -Wall -Wextra -pedantic -g -fPIC

BIN= tail wordcount wordcount-dynamic

.PHONY: all
all: $(BIN)

tail: tail.o

wordcount: wordcount.o io.o libhtab.a
	$(CC) wordcount.o io.o -static -L. -lhtab -o wordcount

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) wordcount.o io.o -L. -Wl,-rpath=. -lhtab -o wordcount-dynamic

libhtab.a: htab_hash_func.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_for_each.o htab_erase.o htab_clear.o htab_free.o
	ar rcs $@ $^

libhtab.so: htab_hash_func.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_for_each.o htab_erase.o htab_clear.o htab_free.o
	cc -shared -fPIC $^ -o $@

io.o: io.c io.h

htab_%.o: htab_%.c htab.h htab_internal.h

.PHONY: pack
pack:
	 zip xmatus36.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	-rm -f *.o $(BIN)

