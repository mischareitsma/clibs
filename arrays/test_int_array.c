#include <stdio.h>
#include <stdlib.h>

#include "int_array.h"

int main()
{
	IntArray *arr = malloc(sizeof(IntArray));
	printf("init\n");
	int_array_init(&arr,5);
	int_array_print(arr,0);
	int_array_add(arr, 12);
	int_array_add(arr, 21);
	int_array_add(arr, 31);
	int_array_print(arr, 0);
	int_array_remove(arr, 1);
	int_array_print(arr, 0);

	int_array_add(arr, 5);
	int_array_add(arr, 5);
	int_array_add(arr, 5);
	if (int_array_add(arr, 5) != 0) {
		printf("Oh no, cannot add!");
	}

	int_array_print(arr, 0);

	int_array_resize(&arr, 10);
	int_array_print(arr, 0);
	int_array_add(arr, 1234);
	int_array_print(arr, 0);

	free(arr);
}