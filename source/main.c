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

	const int k1_ = 3; const char v1_[] = "value 1";
	const char k2_[] = "string"; const char v2_[] = "value 2";

	hm_add(hmap, &k1_, sizeof(k1_), v1_);
	hm_add(hmap, &k2_, sizeof(k2_), v2_);

	puts((char*)hm_get(hmap, &k1_, sizeof(k1_)));
	puts((char*)hm_get(hmap, &k2_, sizeof(k2_)));

	hm_free(hmap);
	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#.+"-)W(?=[-a-z]+"$)/gm
