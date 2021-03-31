#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "io.h"

#define MAX_WORD_LEN 128

// prints the given htab item to stdout
void htab_print(htab_pair_t *item)
{
    printf("%s\t%d\n", item->key, item->value);
}

int main(void)
{
    htab_t *t = htab_init(3500);
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

    htab_for_each(t, &htab_print);

    htab_free(t);
    return EXIT_SUCCESS;
}
