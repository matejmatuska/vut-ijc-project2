#ifndef _HTAB_INTERNAL_
#define _HTAB_INTERNAL_

#include "htab.h"

//TODO maybe add htab_item typedef
struct htab_item {
    struct htab_item *next; // points to the next record
    struct htab_pair pair; // public api
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item arr[];
};

#endif // _HTAB_INTERNAL_
