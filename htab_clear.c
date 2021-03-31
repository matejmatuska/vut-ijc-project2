#include <stdlib.h>
#include <stdio.h>

#include "htab.h"
#include "htab_internal.h"

void htab_clear(htab_t *t)
{
    if (t == NULL)
    {
        fprintf(stderr, "htab_clear: htab is NULL\n");
        return;
    }

    // for each bucket
    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *head = t->arr[i];
        while (head != NULL)
        {
            struct htab_item *tmp = head;
            head = tmp->next;

            free((void*)tmp->pair.key);
            free(tmp);
        }
    }
}
