// htab_clear.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdlib.h>

#include "htab.h"
#include "htab_internal.h"

void htab_clear(htab_t *t)
{
    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *head = t->arr[i];
        while (head != NULL)
        {
            struct htab_item *tmp = head;
            head = tmp->next;

            free((char*)tmp->pair.key);
            free(tmp);
        }
    }

    t->arr_size = 0;
    t->size = 0;
}
