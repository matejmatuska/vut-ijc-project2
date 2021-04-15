// htab_hash_func.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <inttypes.h>

#include "htab.h"

size_t htab_hash_function(htab_key_t str)
{
    uint32_t h = 0; // must be 32 bits
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;

    return h;
}
