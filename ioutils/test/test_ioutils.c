#include "ioutils.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Start test_ioutils\n");

	printf("Writing a string to test.log\n");
	write_file("This is a string\n", 17, "test.log");
	
	printf("Now appending to same file\n");
	append_file("This is appended\n", 17, "test.log");

	printf("Now going to read test.log\n");

	char *content = NULL;

	size_t size = read_file(&content, "test.log");

	printf("Read file content, total number of chars: %zu\n", size);
	printf("Content:\n%s", content);
	free(content);

	printf("End test_ioutils\n");
}