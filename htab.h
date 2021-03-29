//TODO documentation wording and @file docs

#ifndef _HTAB_H_
#define _HTAB_H_

#include <string.h>
#include <stdbool.h>

/**
 * The hash table
 */
struct htab;
typedef struct htab htab_t;

/**
 * Hash table key data type
 */
typedef const char *htab_key_t;
/**
 * Hash table value data type
 */
typedef int htab_value_t;

/**
 * Hash table record data type
 */
typedef struct htab_pair {
    htab_key_t key;
    htab_value_t value;
} htab_pair_t;

// TODO document hashing function?
size_t htab_hash_function(htab_key_t str);

/**
 * Constructor:
 * Creates and initializes hash table
 *
 * @param n Number of elements in array (.arr_size)
 * @return The initialized hash table or NULL if memory alocation failed
 */
htab_t *htab_init(size_t n);

/**
 * Move constructor:
 * Creates and initializes a new hash table by moving data from existing hash table
 *
 * @param n //TODO whats this
 * @param from The hash table to move data from
 * @return The new hash table with data from "from"
 */
htab_t *htab_move(size_t n, htab_t *from);

/**
 * Returns number of items in the hash table
 *
 * @return number of items in "t"
 */
size_t htab_size(const htab_t *t);


/**
 * Retuns number of items in array
 */
size_t htab_bucket_count(const htab_t *t);

/**
 * Searches for a record matching the given string key,
 * if such record is found it is returned, otherwise NULL is returned
 *
 * @param key The key of the record to find
 * @return The found record or NULL if no such record was found
 */
htab_pair_t *htab_find(htab_t *t, htab_key_t key);

/**
 * Searches for a record matching the given string key,
 * if such a record is found it is returned,
 * otherwise it is addded to the table and returned.
 * If adding the item fails NULL is returned.
 *
 * @param key The key of record to find
 * @return The found item, a pointer to the newly added item or NULL in case of error
 */
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key);

/**
 * Deletes record with the given key from the table
 *
 * @return true if record was deleted, false otherwise
 */
bool htab_erase(htab_t *t, htab_key_t key);

/**
 * Iterates through all record in the table and calls a function one every one of them
 *
 * @param t the hash table
 * @param f the function to be called on each record
 */
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data));

/**
 * Clears all record in the hash table
 */
void htab_clear(htab_t *t);

/**
 * Destructor:
 * Clears and frees the table
 */
void htab_free(htab_t *t);

#endif // _HTAB_H_
