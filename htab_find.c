// htab_find.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include "htab.h"
#include "htab_internal.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    struct htab_item *tmp = t->arr[index];

    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
            return &(tmp->pair); // found the item

        tmp = tmp->next;
    }

    return NULL;
}
