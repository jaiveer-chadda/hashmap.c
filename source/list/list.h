/// @file list/list.h

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct l__llist *LList;
typedef ssize_t idx_t;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void);
void ll_free(LList list);

void **ll_to_arr(LList list);
LList ll_from_arr(const void *const *const array, size_t len);

idx_t ll_append(LList list, const void *const val);
size_t ll_len(const LList list);

const void *ll_get(const LList list, const idx_t idx);
const void *ll_pop(LList list, const idx_t idx);

#define ll_iter_reset() ll_iter(NULL)
const void *ll_iter(const LList list);
void ll_dump(const LList list, const char *const fmt);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !LIST_H */
