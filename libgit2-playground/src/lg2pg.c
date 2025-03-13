#include <stdio.h>
#include <git2.h>

#include "lg2pg_demo.h"

int main(int argc, char** argv)
{

	for (int i = 0; i < argc; i++) {
		printf("Argument %i: %s\n", i, argv[i]);
	}

	demo_libgit2(argv[1]);

	return 0;
}