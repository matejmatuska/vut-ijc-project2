#include <stdlib.h>

#include "htab.h"
#include "htab_internal.h"

htab_t *htab_init(size_t n)
{
    if (n < 1)
    {
        //TODO args error hnadling
    }

    return malloc(sizeof(htab_t*) + n * sizeof(struct htab_item));
}
