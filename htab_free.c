#include <stdlib.h>
#include <stdio.h>

#include "htab.h"

void htab_free(htab_t *t)
{
    if (t == NULL)
    {
        fprintf(stderr, "htab_free: htab is NULL\n");
        return;
    }

    htab_clear(t);
    free(t);
}
