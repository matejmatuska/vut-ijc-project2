#include <stdlib.h>
#include <stdio.h>

#include "htab_internal.h"
#include "htab.h"

htab_t *htab_init(size_t n)
{
    if (n == 0)
    {
        //TODO args error hnadling
        fprintf(stderr, "error: htab_init, size must be > 0, was: %lu", n);
        return NULL;
    }

    htab_t *t = malloc(sizeof(htab_t) + n * sizeof(struct htab_item*));
    if (t != NULL)
    {
        t->size = 0;
        t->arr_size = n;
    }
    return t;
}
