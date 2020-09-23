#include <stdio.h>
#include <stdlib.h>

#include "int_array.h"

int int_array_init(IntArray **array, int max)
{
	(*array)->max = max;
	(*array)->size = 0;

	(*array)->elements = malloc(max * sizeof(int));

	if ((*array)->elements == NULL) {
		return -1;
	}

	for (int i = 0; i < max; i++) {
		(*array)->elements[i] = 0;
	}
	return 0;
}

int int_array_add(IntArray *array, int i)
{
	if (array->size == array->max) {
		return -1;
	}
	array->elements[array->size] = i;
	array->size +=1;
	return 0;
}

void int_array_print(IntArray *array, int print_option)
{
	printf("IntArray with max size %d, and current size %d\n\n",
		array->max, array->size);
	for(int i = 0; i < array->size; i++) {
		printf("Element %d: %d\n", i, array->elements[i]);
	}
}


int int_array_remove(IntArray *array, int index)
{
	if (!(index < array->size)) {
		return -1;
	}
	if (index < 0) {
		return -1;
	}
	
	/*
	index     | 0 | 1 | 2 | 3 | 4 | 5
	value old | 6 | 9 | 4 | 1 | 5 | X
	value new | 6 | 9 | 1 | 5 | X | X

	- size = 5
	- index = 2
	- Value of index 3 moves to index 2
	- Value of index 4 moves to index 3
	- i = 2, move i+1 to i
	- i = 3, move i+1 to i
	- i = 5, set to 0 if necessary (introduce option later, do for now)
	 */
	for (int i = index; i < array->size - 1; i++) {
		array->elements[i] = array->elements[i+1];
	}
	array->size--;
	array->elements[array->size] = 0; //Later on option.

	return 0;
}

// TODO: This can be an *array, but then only realloc the elements!
int int_array_resize(IntArray **array, int new_size)
{
	if (new_size < 0) {
		return -1;
	}

	IntArray *old_array = *array;
	if (!(new_size > old_array->max)) {
		return -1;
	}

	IntArray *new_array = malloc(sizeof(IntArray));
	int_array_init(&new_array, new_size);

	for (int i = 0; i < old_array->size; i++) {
		new_array->elements[i] = old_array->elements[i];
	}
	new_array->size = old_array->size;
	free(old_array);
	old_array = new_array;

	return 0;
}

// int int_array_clear(IntArray *array, int option);