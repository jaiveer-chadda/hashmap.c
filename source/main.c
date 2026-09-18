/// @file main.c

#include <stdio.h>
#include <stdlib.h>

#include "list/list.h"
#include "hash/hash.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

int main(const int argc, const char *argv[]) {
	LList llist = ll_init();
	if (llist == NULL) return 1;

	ll_append(llist, "entry 0");
	ll_append(llist, "entry 1");
	ll_append(llist, "entry 2");
	ll_append(llist, "entry 3");
	ll_append(llist, "entry 4");
	ll_append(llist, "entry 5");
	ll_append(llist, "entry 6");
	ll_append(llist, "entry 7");
	ll_append(llist, "entry 8");
	ll_append(llist, "entry 9");
	ll_append(llist, "entry 10");

	printf("popped '%s'\n", (char*)ll_pop(llist, 3));
	ll_dump(llist, "%s");

	char **arr = (char**)ll_to_arr(llist);
	const size_t list_len = ll_len(llist);
	ll_free(llist);

	LList llist_2 = ll_from_arr((const void**)arr, list_len);
	free(arr);

	ll_dump(llist_2, "%s");
	ll_free(llist_2);

	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#pragma.*"-)W(?=[-a-z]+"$)/gm
