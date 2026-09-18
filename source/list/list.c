/// @file list/list.c

#include "list.h"

typedef struct l__llist *const LList;
typedef struct l__listitem LLItem;

struct l__llist {
	LLItem *head, *tail;
	ssize_t len;
};

struct l__listitem {
	LLItem *next;
	char *val;
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void) {
	return NULL;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

size_t ll_append (LList list, const char *const val);

/* —————————————————————————————————————————————————— */

char *ll_get(const LList list, const size_t idx);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool ll_rem_idx(LList list, const size_t idx);

/* —————————————————————————————————————————————————— */

bool ll_rem_val(LList list, const char *const val);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
