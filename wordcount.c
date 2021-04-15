#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "io.h"

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
    htab_t *t = htab_init(3500); //TODO choose appropriate size
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
