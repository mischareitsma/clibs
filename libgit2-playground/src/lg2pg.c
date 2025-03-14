#include <stdio.h>
#include <git2.h>

#include "lg2pg_demo.h"

int call_function(int (*add)(int, int), int a, int b);
int add_ints(int a, int b);

int main(int argc, char** argv)
{

	for (int i = 0; i < argc; i++) {
		printf("Argument %i: %s\n", i, argv[i]);
	}

	demo_libgit2(argv[1]);
	int c = call_function(&add_ints, 1, 2);
	printf("c: %d\n", c);

	return 0;
}

int call_function(int (*add)(int, int), int a, int b) {
	return add(a, b);
}

int add_ints(int a, int b) {
	return a+b;
}