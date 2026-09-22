/// @file main.c

#include <stdio.h>
#include "map/map.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

typedef char str[];

int main(const int argc, const char *argv[]) {
	HashMap hmap = hm_init();

	const int	k1_ = 3;
	const str	k2_ = "str";
	const char	k3_ = 'x';

	const str	v1_ = "value 1";
	const str	v2_ = "value 2";
	const str	v3_ = "value 3";

	hm_adds(hmap, k1_, v1_);
	hm_adds(hmap, k2_, v2_);

	hm_pops(hmap, k2_);

	puts(hm_gets(hmap, k1_));
	puts(hm_gets(hmap, k2_));
	puts(hm_gets(hmap, k3_));

	hm_free(hmap);
	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#.+"-)W(?=[-a-z]+"$)/gm
