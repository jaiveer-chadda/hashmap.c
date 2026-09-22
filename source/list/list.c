/// @file list/list.c

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* —— Macro Definitions ———————————————————————————————————————————————————————————————————————————————————————————— */

/** @brief Check if the value `check` is NULL. If it is, print a warning and return `ret`. */
#define RETURN_IF_NULL(check, ret) do {	\
	if ((check) == NULL) {				\
		fprintf(stderr,					\
			"%s: warning: %s\n",		\
			__func__, strerror(errno)	\
		);								\
		return ret;						\
	}									\
} while (0)

/* —————————————————————————————————————————————————— */

/** @brief Print an error and hard-exit the program. */
#define EXIT_FATAL(caller, fmt, ...) do {		\
	fprintf(stderr, ("%s: error: " fmt "\n"),	\
		(caller) __VA_OPT__(,) __VA_ARGS__		\
	);											\
	exit(EXIT_FAILURE);							\
} while (0)

/** @brief Print an out-of-range error, specifying the length and index, then exit. */
#define IDX_OOR_ERROR(caller, llist, index) \
	EXIT_FATAL(caller, "index %ld is out of range for list of length %lu", (index), (llist)->len)

/* —— Typedefs & Structs ——————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct LLItem LLItem;

struct l__llist {
	LLItem *head, *tail;
	size_t len;
};

struct LLItem {
	LLItem *next;
	const void *val;
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_len() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

size_t ll_len(const LList list) {
	RETURN_IF_NULL(list, -1);
	return list->len;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_init() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void) {
	LList list = calloc(1, sizeof(struct l__llist));
	RETURN_IF_NULL(list, NULL);

	return list;
}

/* —— ll_free() ————————————————————————————————————— */

void ll_free(LList list) {
	// if the list is NULL, then print an error and return
	RETURN_IF_NULL(list,);

	LLItem **item_ptrs = malloc(list->len * sizeof(LLItem*));
	LLItem *current = list->head;

	// we have to iterate through the list and save all the pointers that need to be freed
	//	this could also be done recursively, but honestly, this is easier.
	for (size_t i = 0; i < list->len; i++) {
		item_ptrs[i] = current;
		current = current->next;
	}

	for (size_t i = 0; i < list->len; i++) {
		free(item_ptrs[i]);
	}

	free(item_ptrs);
	free(list);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_to_arr() —————————————————————————————————————————————————————————————————————————————————————————————————— */

void **ll_to_arr(const LList list) {
	const void **array = calloc(list->len, sizeof(void*));
	RETURN_IF_NULL(array, NULL);

	const LLItem *current = list->head;
	// we have to iterate through the list and save all the pointers that need to be freed
	//	this could also be done recursively, but honestly, this is easier.
	for (size_t i = 0; i < list->len; i++) {
		array[i] = current->val;
		current = current->next;
	}

	return (void**)array;
}

/* —— ll_from_arr() ———————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_from_arr(const void *const *const array, const size_t len) {
	LList list = ll_init();
	RETURN_IF_NULL(list, NULL);

	for (size_t i = 0; i < len; i++) ll_append(list, array[i]);
	return list;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_append() —————————————————————————————————————————————————————————————————————————————————————————————————— */

idx_t ll_append(LList list, const void *const val) {
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

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— normalise_index() ———————————————————————————————————————————————————————————————————————————————————————————— */

#define XNOR ==

#define normalise_index(llist, index) \
	l__normalise_index(__func__, (llist), (index))

static inline idx_t l__normalise_index(const char *const caller, const LList list, const idx_t idx) {
	// there should never be a case in which the head or tail is NULL, and the other one isn't
	assert((list->head == NULL) XNOR (list->tail == NULL));

	// equally, whenever the head and/or tail is NULL, the length should be 0
	assert((list->head == NULL) XNOR (list->len == 0));
	assert((list->tail == NULL) XNOR (list->len == 0));

	// make a copy of the index which we can manipulate as needed
	idx_t index = idx;

	// if the user requests the last element, then just return the linked list's tail
	if (index == -1 || index == (idx_t)(list->len - 1)) {
		// that is, unless the list is empty
		if (list->len == 0) IDX_OOR_ERROR(caller, list, index);
		return (idx_t)(list->len - 1);
	}

	// make sure that the list is long enough to accommodate this index
	if (index >= (idx_t)list->len) IDX_OOR_ERROR(caller, list, index);

	// if the index entered was negative, then convert it into its positive counterpart
	if (index <= -1) {
		index = list->len + idx;
		// check that the index is still in range
		if (index < 0) IDX_OOR_ERROR(caller, list, idx);
	}

	return index;
}

/* —— ll_get() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

const void *ll_get(const LList list, const idx_t idx) {
	// don't try and operate on a list that points to NULL
	RETURN_IF_NULL(list, NULL);

	const idx_t index = normalise_index(list, idx);
	if (index == (idx_t)(list->len - 1)) return list->tail->val;

	// iterate through the list until we find the index requested
	const LLItem *current = list->head;
	for (idx_t i = 0; i < index; i++) {
		current = current->next;
		assert(current != NULL);
	}

	return current->val;
}

/* —— ll_pop() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

const void *ll_pop(LList list, const idx_t idx) {
	// don't try and operate on a list that points to NULL
	RETURN_IF_NULL(list, NULL);

	const idx_t index = normalise_index(list, idx);

	LLItem *prv_item = NULL;       /** The item before the item to delete; NULL if deleting the head. */
	LLItem *del_item = list->head; /** The item to delete. */

	for (idx_t i = 0; i < index; i++) {
		// keep updating the previous item and the item to delete
		prv_item = del_item, del_item = del_item->next;
		// `del_item` shouldn't be able to be NULL, since the loop is bounded by `index`, which should be `< list.len`
		assert(del_item != NULL);
	}

	LLItem *const nxt_item = del_item->next; /** The item after the item to delete. */

	// update the head directly if there's no previous item
	if (prv_item == NULL) list->head = nxt_item;
	// and just relink around the deleted item if everything exists
	else prv_item->next = nxt_item;

	// if we're about to delete the tail, the new tail is whatever was before it (`NULL` if the list is now empty)
	if (del_item == list->tail) list->tail = prv_item;

	const void *const retval = del_item->val; // save the deleted item's value so it can be returned.
	free(del_item);	// delete the item by freeing its memory

	list->len--;	// decrement the list's length
	return retval;	// and finally, return the value that was held by the now-deleted item
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_iter() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

const void *l__iter(const LList list, const bool do_reset) {
	// the active item being tracked by this iterator
	static const LLItem *current = NULL;

	// this is just some simple overloading, so I don't have to do anything complicated when resetting the iterator
	if (do_reset) return ( current = NULL ); // the retval here doesn't matter - this is just a concise way to do it

	// if the input was NULL (and we're not resetting), then print an error, and return NULL
	RETURN_IF_NULL(list, NULL);

	// if the iteration has just started, set `current` to the first element, otherwise, move onto the next element
	current = (current == NULL) ? list->head : current->next;

	// if the first/next element is `NULL`, then we've reached the end of the list - return NULL
	if (current == NULL) return NULL;
	// otherwise, return the new item's value
	return current->val;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_dump() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

void ll_dump(const LList list, const char *const fmt) {
	if (list == NULL) { puts("NULL"); return; }

	printf("length = %zu", list->len);

	// calculate the max length of the index, for ease of printing
	//	sure, this could be done a better way, but `ll_dump` is mostly used for debugging, so it doesn't rly matter
	const int idxlen = snprintf(NULL, 0, "%zd", (idx_t)(list->len - 1));

	// set up all the iterator variables
	const void *value;
	idx_t idx = 0;
	ll_iter_reset();

	// print each item's index, along with its value, using the format specifier provided
	while (( value = ll_iter(list) )) {
		printf("\n[%*zd] = ", idxlen, idx++);
		printf(fmt, value);
	}

	putchar('\n');
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
