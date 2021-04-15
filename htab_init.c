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
