/// @file main.c

#include <stdio.h>

#include "list/list.h"
#include "hash/hash.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"

int main(const int argc, const char *argv[]) {
	const char input1[] = "hello";
	const char input2[] = "ehllo";
	const int  input3	= 0;

	printf("%s --> %u\n", input1, hash(&input1, sizeof(input1)));
	printf("%s --> %u\n", input2, hash(&input2, sizeof(input2)));
	printf("%d --> %u\n", input3, hash(&input3, sizeof(input3)));

	return 0;
}

#pragma clang diagnostic pop

// spell:ignoreRegExp /(?<=^#pragma.*"-)W(?=[-a-z]+"$)|"\w+"/gm
