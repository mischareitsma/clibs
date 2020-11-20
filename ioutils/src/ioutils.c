#include <stdio.h>
#include <stdlib.h>

#include "ioutils.h"

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

	// If malloc fails, return 0. Even an empty file would return 1.
	if (! buffer)
		return 0;

	// Read all bytes and put in buffer, set last byte to \0
	fread(buffer, size, 1, fp);
	buffer[size] = '\0';

	fclose(fp);

	*content = buffer;

	return size;
}

void write_file(char *content, size_t content_size, char *filelocation)
{
	FILE *fp = fopen(filelocation, "wb");
	fwrite(content, sizeof(char), content_size, fp);
	fclose(fp);
}

void append_file(char *content, size_t content_size, char *filelocation)
{
	FILE *fp = fopen(filelocation, "ab");
	fwrite(content, sizeof(char), content_size, fp);
	fclose(fp);
}
