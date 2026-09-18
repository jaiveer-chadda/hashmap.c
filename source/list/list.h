/// @file list/list.h

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct l__llist *const LList;
typedef ssize_t idx_t;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void);
void  ll_free(LList list);
idx_t ll_append	(LList list, const char *const val);
bool  ll_rem_val(LList list, const char *const val);
bool  ll_rem_idx(LList list, const idx_t idx);
const char *ll_get(const LList list, const idx_t idx);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !LIST_H */
