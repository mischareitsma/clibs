#ifndef __IOUTILS_H__
#define __IOUTILS_H__

#include <stddef.h>

size_t read_file(char **content, char *filelocation);
void write_file(char *content, size_t content_size, char *filelocation);
void append_file(char *content, size_t content_size, char *filelocation);

#endif /* __IOUTILS_H__ */