#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "htab_internal.h"

// initializes new htab_item with the given key
// initial value of value is 0
struct htab_item *htab_item_init(htab_key_t key)
{
    struct htab_item *item = malloc(sizeof(struct htab_item)); 
    if (item != NULL)
    {
        char *tmp = malloc(strlen(key) + 1);
        if (tmp == NULL)
            return NULL;

        item->pair.key = strcpy(tmp, key);
        item->pair.value = 0;
        item->next = NULL;
    }
    return item;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    if (t == NULL || key == NULL)
    {
        //TODO args checking
        fprintf(stderr, "htab_lookup_add: null arg\n");
        return NULL;
    }

    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    struct htab_item *tmp = t->arr[index]; // get the bucket

    if (tmp == NULL)
    {
        // bucket is empty insert the new item directly
        struct htab_item *item = htab_item_init(key);
        t->arr[index] = item;
        t->size++;
        return &(item->pair);
    }

    while (tmp->next != NULL) // bucket is not empty, search for item
    {
        if (strcmp(tmp->pair.key, key) == 0)
            return &(tmp->pair); // item found, reuturn it

        tmp = tmp->next;
    }

    // item wasnt found, insert it at the end of the linked list
    tmp->next = htab_item_init(key);
    if (tmp->next != NULL)
    {
        t->size++;
        return &(tmp->next->pair);
    }

    return NULL;
}