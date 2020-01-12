#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

size_t read_file(char **content, char *filelocation)
{
	char *buffer = 	NULL;

	FILE *fp = fopen(filelocation, 	"rb");

	// Seek end to get the total size, then reset to beginning.
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);

	// Allocate bytes + 1 for \0
	buffer = malloc((size + 1) * sizeof(char));

	// Read all bytes and put in buffer, set last byte to \0
	fread(buffer, size, 1, fp);
	buffer[size] = '\0';

	fclose(fp);

	*content = buffer;

	return size;
}
