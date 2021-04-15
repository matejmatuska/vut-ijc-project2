// htab_free.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdlib.h>

#include "htab.h"

void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t);
}
