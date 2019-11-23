#include <stdio.h>
#include <stdlib.h>
#include "strarr.h"

int main()
{
	printf("Testing String arrays");
	// Test the init and init default
	printf("Start init default size\n");
	StringArray *sa1 = malloc(sizeof(StringArray));
	strarr_init_default(&sa1);
	strarr_print(sa1);
	
	printf("Start init size of 3\n");
	StringArray *sa2 = malloc(sizeof(StringArray));
	strarr_init(&sa2, 3);
	strarr_print(sa2);

	printf("Adding four strings, fourth one should exit with %d\n", STRARR_COULD_NOT_ADD);
	printf("Adding 'one', ret = %d\n", strarr_add(sa2, "one"));
	printf("Adding 'two', ret = %d\n", strarr_add(sa2, "two"));
	printf("Adding 'three', ret = %d\n", strarr_add(sa2, "three"));
	printf("Adding 'four', ret = %d\n", strarr_add(sa2, "four"));

	printf("Current content of sa2\n");
	strarr_print(sa2);

	printf("Remove element at index 0\n");
	strarr_remove_at_index(sa2, 0);
	printf("Now the content:\n");
	strarr_print(sa2);
	printf("The string 'three' is now at index %d\n", strarr_find_match(sa2, "three", 0));
	printf("Removing 'three' and printing\n");
	strarr_remove_match(sa2, "three");
	strarr_print(sa2);

	strarr_add(sa2, "one");
	strarr_add(sa2, "three");
	
	printf("sa2 should be full again:\n");
	strarr_print(sa2);
	printf("Resizing to hold 3 more elements\n");
	strarr_resize(sa2, 6);
	printf("After resizing:\n");
	strarr_print(sa2);
	strarr_add(sa2, "Four");
	strarr_add(sa2, "Five");
	strarr_print(sa2);


	// Adding a lot of things in sa1 and printing
	strarr_add(sa1, "Hello World");
	strarr_add(sa1, "Hi there");
	strarr_add(sa1, "strarr_add");
	strarr_add(sa1, "Hello World");
	strarr_add(sa1, "Hello World");
	strarr_add(sa1, "Hallo Wereld");
	strarr_add(sa1, "This is a bit longer string, this should still work?");
	strarr_add(sa1, "Hello world");
	strarr_add(sa1, "Ahoy hoy");
	strarr_add(sa1, "Hello World");
	strarr_print(sa1);

	printf("Removing all that are \"Hello World\"\n");
	strarr_remove_match_all(sa1, "Hello World");
	strarr_print(sa1);

	StringArray *sa3 = malloc(sizeof(StringArray));
	strarr_init(&sa3, 10);
	strarr_copy_elements(sa2, sa3, 1, 3);
	printf("After copying three elements (elem 1,2 and 3) from sa2 to sa3\n");
	printf("Content sa2\n");
	strarr_print(sa2);

	printf("Content sa3\n");
	strarr_print(sa3);

	printf("Clearing sa2\n");
	strarr_clear(sa2);
	strarr_print(sa2);

	strarr_delete(&sa1);
	strarr_delete(&sa2);
	strarr_delete(&sa3);

	free(sa1);
	free(sa2);
	free(sa3);
}