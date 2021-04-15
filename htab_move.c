#include "htab.h"
#include "htab_internal.h"

htab_t *htab_move(size_t n, htab_t *from)
{
    htab_t *t = htab_init(n);
    if (t == NULL)
        return NULL;

    t->arr_size = n;
    t->size = htab_size(from);

    for (size_t i = 0; i < from->arr_size; i++)
    {
        struct htab_item *head = from->arr[i];
        while (head != NULL)
        {
            htab_key_t key = head->pair.key;
            htab_value_t val = head->pair.value;

            htab_pair_t *item = htab_lookup_add(t, key);
            item->value = val;

            head = head->next;
        }
    }

    htab_clear(from);
    return t;
}

