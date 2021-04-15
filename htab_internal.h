// htab_internal.h
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef _HTAB_INTERNAL_
#define _HTAB_INTERNAL_

#include "htab.h"

struct htab_item {
    struct htab_item *next; // points to the next record
    struct htab_pair pair; // public api
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};

#endif // _HTAB_INTERNAL_
