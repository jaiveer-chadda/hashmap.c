/// @file list/list.c

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define XNOR ==

#define LLIST_ASSERTIONS(llist) do { \
	/* there should never be a case in which the head or tail is NULL, and the other one isn't */ \
	assert((llist->head == NULL) XNOR (llist->tail == NULL)); \
	/* equally, whenever the head and/or tail is NULL, the length should be 0 */ \
	assert((llist->head == NULL) XNOR (llist->len == 0 )); \
	assert((llist->tail == NULL) XNOR (llist->len == 0 )); \
} while (0)

/* —————————————————————————————————————————————————— */

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

/* —————————————————————————————————————————————————— */

/** @brief Print an error and hard-exit the program. */
#define EXIT_FATAL(fmt, ...) do {				\
	fprintf(stderr, ("%s: error: " fmt "\n"),	\
		__func__ __VA_OPT__(,) __VA_ARGS__		\
	);											\
	exit(EXIT_FAILURE);							\
} while (0)

/** @brief Print an out-of-range error, specifying the length and index, then exit. */
#define IDX_OOR_ERROR(llist, index) \
	EXIT_FATAL("index %ld is out of range for list of length %lu", (index), (llist)->len)

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
	LList list = calloc(1, sizeof(struct l__llist));
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

const char *ll_get(const LList list, const idx_t idx) {
	LLIST_ASSERTIONS(list);

	// make a copy of the index which we can manipulate as needed
	idx_t index = idx;

	// if the user requests the last element, then just return the linked list's tail
	if (index == -1 || index == (idx_t)(list->len - 1)) {
		// that is, unless the list is empty
		if (list->len == 0) IDX_OOR_ERROR(list, index);
		return list->tail->val;
	}

	// make sure that the list is long enough to accommodate this index
	if (index >= (idx_t)list->len) IDX_OOR_ERROR(list, index);

	// if the index entered was negative, then convert it into its positive counterpart
	if (index <= -1) {
		index = list->len + idx;
		// check that the index is still in range
		if (index < 0) IDX_OOR_ERROR(list, idx);
	}

	// iterate through the list until we find the index requested
	const LLItem *current = list->head;
	for (idx_t i = 0; i < index; i++) {
		current = current->next;
		assert(current != NULL);
	}

	return current->val;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool ll_rem_idx(LList list, const idx_t idx);

/* —————————————————————————————————————————————————— */

bool ll_rem_val(LList list, const char *const val);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
