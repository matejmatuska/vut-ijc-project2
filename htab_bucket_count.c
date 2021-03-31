#include "htab.h"
#include "htab_internal.h"

size_t htab_bucket_count(const htab_t *t)
{
    if (t == NULL)
    {
        //TODO error handling
        return -1;
    }
    return t->arr_size;
}
