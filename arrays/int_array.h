#ifndef __INT_ARRAY__
#define __INT_ARRAY__

#include <stddef.h>

typedef struct {
	int max;
	int size;
	int *elements;
} IntArray;

// TODO: Do need to add all the error #define's for return status
int int_array_init(IntArray **array, int max);
int int_array_add(IntArray *array, int i);
int int_array_remove(IntArray *array, int index);
int int_array_resize(IntArray **array, int new_size);
// int int_array_clear(IntArray *array, int option);

void int_array_print(IntArray *array, int print_option);

#endif