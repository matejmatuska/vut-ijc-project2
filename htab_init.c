// htab_init.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdlib.h>

#include "htab_internal.h"
#include "htab.h"

htab_t *htab_init(size_t n)
{
    if (n == 0)
        return NULL;

    //TODO calloc or memset or manually?? For now it works
    htab_t *t = calloc(sizeof(htab_t) + n * sizeof(struct htab_item*), 1);
    if (t != NULL)
    {
        t->size = 0;
        t->arr_size = n;
    }
    return t;
}
