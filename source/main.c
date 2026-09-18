/// @file main.c

#include <stdio.h>

#include "map/map.h"
#include "list/list.h"
#include "hash/hash.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

int main(const int argc, const char *argv[]) {
	HashMap hmap = hm_init();

	hm_free(hmap);
	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#.+"-)W(?=[-a-z]+"$)/gm
