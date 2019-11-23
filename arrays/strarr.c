#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strarr.h"


int strarr_init_default(StringArray **arr)
{
	return strarr_init(arr, STRARR_DEFAULT_SIZE);
}

int strarr_init(StringArray **arr, int size)
{
	if (size < 0) {
		return STRARR_INVALID_SIZE;
	}

	StringArray *sa = *arr;
	
	sa->elem = malloc(size * sizeof(char*));

	if (!sa->elem) {
		return STRARR_COULD_NOT_INITIALIZE;
	}

	sa->max_size = size;
	sa->size = 0;

	return STRARR_SUCCESS;
}

// Resize can only make things bigger, for smaller there should be a copy func
int strarr_resize(StringArray *arr, int new_size)
{
	if (new_size < arr->max_size) {
		return STRARR_INVALID_SIZE_FOR_RESIZING;
	}

	char **tmp = realloc(arr->elem, new_size * sizeof(char *));
	if (!tmp) {
		return STRARR_COULD_NOT_RESIZE;
	}
	arr->elem = tmp;
	arr->max_size = new_size;
	return STRARR_SUCCESS;
}

int strarr_delete(StringArray **arr)
{
	if (*arr == NULL) {
		// Nothing to delete.
		return STRARR_SUCCESS;
	}
	StringArray *sa = *arr;

	// Free all content
	for (int i = 0; i < sa->size; i++) {
		free(sa->elem[i]);
		sa->elem[i] = NULL;
	}
	free(sa->elem);
	sa->size = 0;
	sa->max_size = 0;
	return STRARR_SUCCESS;
}

int strarr_add(StringArray *arr, char *str)
{
	if (!(arr->size < arr->max_size)) {
		return STRARR_ARRAY_FULL;
	}

	char *elem = strdup(str);
	if (elem == NULL) {
		return STRARR_COULD_NOT_ADD;
	}

	arr->elem[arr->size] = elem;
	arr->size++;

	return STRARR_SUCCESS;
}

int strarr_remove_at_index(StringArray *arr, int index)
{
	if (index < 0 || index > (arr->size - 1)) {
		return STRARR_INVALID_INDEX;
	}

	free(arr->elem[index]);

	for (int i = index; i < arr->size - 1; i++) {
		arr->elem[i] = arr->elem[i+1];
	}

	arr->size--;
	arr->elem[arr->size] = NULL;

	return STRARR_SUCCESS;
}

int strarr_find_match(StringArray *arr, char *str, int start_from_index)
{
	if (start_from_index < 0) {
		return STRARR_INVALID_INDEX;
	}

	for(int i = start_from_index; i < arr->size; i++) {
		if (strcmp(str, arr->elem[i]) == 0) {
			return i;
		}
	}

	return STRARR_NO_MATCH_FOUND;
}

int strarr_remove_match(StringArray *arr, char *str)
{
	int index = strarr_find_match(arr, str, 0);
	if (index == STRARR_NO_MATCH_FOUND) {
		return STRARR_NOTHING_TO_REMOVE;
	}
	// Should return SUCCESS, but in case it fails, return that value.
	return strarr_remove_at_index(arr, index);
}

int strarr_remove_match_all(StringArray *arr, char *str)
{
	int i = STRARR_SUCCESS;
	while(i != STRARR_NOTHING_TO_REMOVE) {
		i = strarr_remove_match(arr, str);
	}
	return STRARR_SUCCESS;
}

int strarr_clear(StringArray *arr)
{
	for (int i = 0; i < arr->size; i++) {
		free(arr->elem[i]);
		arr->elem[i] = NULL;
	}

	arr->size = 0;
	arr->max_size = 0;

	return STRARR_SUCCESS;
}

int strarr_copy_elements(StringArray *from_arr, StringArray *to_arr, int start_from_index, int number_of_elements)
{
	if (number_of_elements > to_arr->max_size)
	{
		return STRARR_NO_ROOM_FOR_COPY;
	}

	if (to_arr->size != 0)
	{
		return STRARR_TO_ARRAY_NOT_EMPTY;
	}

	for(int i = start_from_index; (i < (start_from_index + number_of_elements)) && (i < from_arr->size); i++)
	{
		to_arr->elem[to_arr->size++] = strdup(from_arr->elem[i]);
	}
	return STRARR_SUCCESS;
}

void strarr_print(StringArray *arr)
{
	printf("StringArray of max size %d, current size %d\n\n", arr->max_size, arr->size);
	for (int i = 0; i < arr->size; i++) {
		printf("Element %d: %s\n", i, arr->elem[i]);
	}
	printf("\n");
}