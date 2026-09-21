/// @file map/map.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "hash/hash.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define HASH_TABLE_SIZE 128

/// Find the location in the hash table where this key would be stored.
#define keyHash(key, ksize) (hash((key), (ksize)) % HASH_TABLE_SIZE)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef LList bucket_t;

/// @brief The internal struct to which the `HashMap` type points.
struct hm__hashmap {
	bucket_t *table; // array of buckets
};

/// @brief A key-value pair.
typedef struct kvpair_t {
	void *val;
	void *key; size_t ksize;
} kvpair_t;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

HashMap hm_init(void) {
	HashMap hmap = malloc(sizeof(struct hm__hashmap));
	hmap->table = calloc(HASH_TABLE_SIZE, sizeof(bucket_t));
	return hmap;
}

/* —————————————————————————————————————————————————— */

void hm_free(HashMap map) {
	if (map != NULL) {
		if (map->table != NULL) {
			// iterate through all buckets in the table
			for (int i = 0; i < HASH_TABLE_SIZE; i++) {
				bucket_t bucket = map->table[i];
				if (bucket != NULL) {

					ll_iter_reset(); // initialise the bucket iteration

					// iterate through the linked list, getting a pointer to another key-value pair each time
					kvpair_t *pkv_pair;
					while (( pkv_pair = (kvpair_t*)ll_iter(bucket) )) {
						// free the memory allocated for the key, then the pair as a whole
						if (pkv_pair != NULL) {
							if (pkv_pair->key != NULL) {
								free(pkv_pair->key);
							}
							free(pkv_pair);
						}
					}
					ll_free(bucket);
				}
			}
			free((void*)map->table);
		}
		free((void*)map);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void hm_add(HashMap map, const void *const key, const size_t ksize, const void *const value) {
	// get a pointer to the bucket in which we should store this key
	bucket_t *bucket = &map->table[keyHash(key, ksize)];
	// if the bucket doesn't exist yet, then initialise a new one
	if (*bucket == NULL) *bucket = ll_init();

	// allocate memory for the key-value pair
	kvpair_t *pair = malloc(sizeof(kvpair_t));
	*pair = (kvpair_t){
		// allocate some more memory so the key can be duplicated and stored
		.key = memcpy(malloc(ksize), key, ksize),
		.ksize = ksize,
		.val = (void*)value
	};

	// add the key-value pair to the bucket (the linked list)
	ll_append(*bucket, pair);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void *hm_get(HashMap map, const void *const key, const size_t ksize) {
	// find the bucket which this key should be stored in
	const bucket_t bucket = map->table[keyHash(key, ksize)];

	// if a bucket doesn't exist for this key's hash, then we know the key isn't in the hashmap
	if (bucket == NULL) return NULL;

	ll_iter_reset(); // initialise the iteration
	const kvpair_t *elem;

	// iterate through the linked list, and check each stored key against the inputted key
	while (( elem = (kvpair_t*)ll_iter(bucket) )) {
		if (ksize == elem->ksize && memcmp(key, elem->key, ksize) == 0) {
			return elem->val;
		}
	}

	// if we couldn't find any keys that matched the inputted key, then that key isn't in the hashmap either
	return NULL;
}

/* —————————————————————————————————————————————————— */

void *hm_pop(HashMap map, const void *const key, const size_t ksize);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
