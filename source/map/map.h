/// @file map/map.h

#ifndef MAP_H
#define MAP_H

#include "list/list.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct hm__hashmap *HashMap;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

HashMap hm_init(void);
void hm_free(HashMap map);

void  hm_add(HashMap map, const void *const key, const size_t ksize, const void *const value);
void *hm_get(HashMap map, const void *const key, const size_t ksize);
void *hm_pop(HashMap map, const void *const key, const size_t ksize);

#endif /* !MAP_H */
