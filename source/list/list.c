/// @file list/list.c

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/** @brief Check if the value `check` is NULL. If it is, print a warning and return `ret`. */
#define RETURN_IF_NULL(check, ret) do {	\
	if ((check) == NULL) {				\
		fprintf(stderr,					\
			"%s: warning: %s\n",		\
			__func__, strerror(errno)	\
		);								\
		return (ret);					\
	}									\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct l__llist *const LList;
typedef struct LLItem LLItem;

typedef size_t usize_t;

struct l__llist {
	LLItem *head, *tail;
	usize_t len;
};

struct LLItem {
	LLItem *next;
	const char *val;
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void) {
	LList list = calloc(1, sizeof(LLItem));
	RETURN_IF_NULL(list, NULL);

	return list;
}

/* —————————————————————————————————————————————————— */

void ll_free(LList list) {
	if (list != NULL) free(list);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

idx_t ll_append(LList list, const char *const val) {
	// allocate memory for this item, and initialise it with the inputted `val` param
	LLItem *pitem = malloc(sizeof(LLItem));
	RETURN_IF_NULL(pitem, -1);

	*pitem = (LLItem){ .next = NULL, .val = val };

	// if this is the first element, then also set the head to this item
	if (list->head == NULL) list->head = pitem;
	// otherwise, just set the `next` property of the last element
	else list->tail->next = pitem;

	list->tail = pitem; // no matter what, set the tail of the linked list to this item
	return ++list->len; // return the index of the added item
}

/* —————————————————————————————————————————————————— */

char *ll_get(const LList list, const idx_t idx);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool ll_rem_idx(LList list, const idx_t idx);

/* —————————————————————————————————————————————————— */

bool ll_rem_val(LList list, const char *const val);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
