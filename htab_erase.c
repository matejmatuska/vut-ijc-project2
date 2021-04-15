// htab_erase.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdlib.h>

#include "htab.h"
#include "htab_internal.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    struct htab_item *tmp = t->arr[index];

    if (tmp == NULL)
    {
        // bucket is empty
        return false;
    }

    if (strcmp(tmp->pair.key, key) == 0)
    {
        struct htab_item *head = tmp;
        t->arr[index] = tmp->next;
        t->size--;
        free((char*)head->pair.key);
        free(head);
        return true;
    }

    struct htab_item *prev;
    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
        {
            prev->next = tmp->next;
            t->size--;

            free((void*)tmp->pair.key);
            free(tmp);
            return true;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return false;
}
