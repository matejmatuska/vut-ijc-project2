// htab_bucket_count.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include "htab.h"
#include "htab_internal.h"

size_t htab_bucket_count(const htab_t *t)
{
    return t->arr_size;
}
