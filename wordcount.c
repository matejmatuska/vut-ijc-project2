// wordcount.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "io.h"

// I've chosen a prime number to reduce the number of collisions,
// 4111 should be a good balance between space and speed for small aswell as bigger files
#define HTAB_SIZE 4111
#define MAX_WORD_LEN 128

// hash function used if HASHTEST is defined
// copied from http://www.cse.yorku.ca/~oz/hash.html - djb2
#ifdef HASHTEST
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
#endif

// prints the given htab item to stdout
void htab_print(htab_pair_t *item)
{
    printf("%s\t%d\n", item->key, item->value);
}

int main(void)
{
    htab_t *t = htab_init(HTAB_SIZE);
    if (t == NULL)
    {
        fprintf(stderr, "Failed to allocate hash table\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LEN] = { 0, };
    while (read_word(word, MAX_WORD_LEN, stdin) != EOF)
    {
        htab_pair_t *item = htab_lookup_add(t, word);
        if (item == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        item->value++;
    }

#ifdef MOVETEST
    htab_t *t2 = htab_move(10, t);
    htab_free(t);
    t = t2;
#endif

    htab_for_each(t, &htab_print);

    htab_free(t);
    return EXIT_SUCCESS;
}
