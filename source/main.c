/// @file main.c

#include <stdio.h>

#include "list/list.h"
#include "hash/hash.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

int main(const int argc, const char *argv[]) {
	LList llist = ll_init();
	if (llist == NULL) return 1;

	ll_append(llist, "entry 1");
	ll_append(llist, "entry 2");
	ll_append(llist, "entry 3");

	puts(ll_get(llist, -2));

	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#pragma.*"-)W(?=[-a-z]+"$)/gm
