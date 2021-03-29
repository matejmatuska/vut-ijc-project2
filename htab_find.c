#include <stdio.h>

#include "htab.h"
#include "htab_internal.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    if (t == NULL || key == NULL)
    {
        //TODO args checking
        fprintf(stderr, "htab_find: null argument\n");
        return NULL;
    }

    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    struct htab_item *tmp = t->arr[index];

    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
            // found the item 
            return &(tmp->pair);

        tmp = tmp->next;
    }

    return NULL;
}
