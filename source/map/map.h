/// @file map/map.h

#ifndef MAP_H
#define MAP_H

#include "list/list.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct hm__hashmap *HashMap;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

HashMap hm_init(void);
void hm_free(HashMap map);

void hm_add(HashMap map, void *key, void *value);
void hm_get(HashMap map, void *key);
void hm_pop(HashMap map, void *key);

#endif /* !MAP_H */
