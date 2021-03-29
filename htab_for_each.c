#include <stdio.h>

#include "htab.h"
#include "htab_internal.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    //TODO args checking

    // for each bucket
    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *tmp = t->arr[i];
        // for each element in the bucket
        while (tmp != NULL)
        {
            htab_pair_t *data = &(tmp->pair);
            (*f)(data);

            tmp = tmp->next;
        }
    }
}
