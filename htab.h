/**
 * @file htab.h
 * @brief This header contains hashtable interface definiton
 *
 * @author Matej Matuska
 *
 * @date 15.04.2021
 */
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
 * Hash table item key data type
 */
typedef const char *htab_key_t;

/**
 * Hash table item value data type
 */
typedef int htab_value_t;

/**
 * Hash table item data type
 */
typedef struct htab_pair {
    htab_key_t key;
    htab_value_t value;
} htab_pair_t;

/* 
 * Hashing function
 *
 * @param str The key to hash
 * @return hash for the given key
 */
size_t htab_hash_function(htab_key_t str);

/**
 * Creates and initializes new hash table
 *
 * @param n Number of buckets
 * @return The initialized hash table or NULL if memory alocation failed
 */
htab_t *htab_init(size_t n);

/**
 * Creates and initializes a new hash table by moving data from existing hash table
 *
 * @param n Number of buckets of new hash table
 * @param from The hash table to move data from
 * @return new hashtable with data from "from"
 */
htab_t *htab_move(size_t n, htab_t *from);

/**
 * Returns number of items in hash table
 *
 * @param t The hash table
 * @return number of items in the given hash table
 */
size_t htab_size(const htab_t *t);

/**
 * Retuns number of buckets in the given hash table
 *
 * @param t The hash table
 */
size_t htab_bucket_count(const htab_t *t);

/**
 * Searches for an item matching the given string key,
 * if such item is found it is returned, otherwise NULL is returned
 *
 * @param key The key of the item to find
 * @return The found item or NULL if no such item was found
 */
htab_pair_t *htab_find(htab_t *t, htab_key_t key);

/**
 * Searches for an item matching the given string key,
 * if such an item is found it is returned,
 * otherwise it is addded to the table and returned.
 * If adding the item fails NULL is returned.
 *
 * @param key The key of item to find
 * @return The found item, a pointer to the newly added item or NULL in case of error
 */
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key);

/**
 * Deletes item with the given key from the hash table
 *
 * @param t The hash table
 * @param ket The key of item to delete
 * @return true if item was deleted, false otherwise
 */
bool htab_erase(htab_t *t, htab_key_t key);

/**
 * Iterates through all items in hash table and calls a function one every one of them
 *
 * @param t The hash table
 * @param f The function to be called on each item
 */
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data));

/**
 * Clears all items in hash table
 */
void htab_clear(htab_t *t);

/**
 * Clears and frees hash table
 */
void htab_free(htab_t *t);

#endif // _HTAB_H_
