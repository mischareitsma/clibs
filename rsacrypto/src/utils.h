#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

size_t read_file(char **content, char *filelocation);
void write_file(char *content, size_t content_size, char *filelocation);

#endif
