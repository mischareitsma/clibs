#ifndef __STRARR_H__
#define __STRARR_H__

typedef struct {
	int max_size;
	int size;
	char **elem;
} StringArray;

// Constants
#define STRARR_DEFAULT_SIZE 10

// Return values
#define STRARR_NO_MATCH_FOUND -1

#define STRARR_SUCCESS 0

#define STRARR_COULD_NOT_INITIALIZE 1
#define STRARR_INVALID_SIZE 2
#define STRARR_ARRAY_FULL 3
#define STRARR_COULD_NOT_ADD 4
#define STRARR_NOTHING_TO_REMOVE 5
#define STRARR_INVALID_INDEX 6
#define STRARR_INVALID_SIZE_FOR_RESIZING 7
#define STRARR_COULD_NOT_RESIZE 8
#define STRARR_NO_ROOM_FOR_COPY 9
#define STRARR_TO_ARRAY_NOT_EMPTY 10

// Initializing and resizing functions.
int strarr_init_default(StringArray **arr);
int strarr_init(StringArray **arr, int size);
int strarr_resize(StringArray *arr, int new_size);
int strarr_delete(StringArray **arr);

// Adding / removing / replacing etc.

int strarr_add(StringArray *arr, char *str);
int strarr_remove_at_index(StringArray *arr, int index);
int strarr_find_match(StringArray *arr, char *str, int start_from_index);
int strarr_remove_match(StringArray *arr, char *str);
int strarr_remove_match_all(StringArray *arr, char *str);
int strarr_clear(StringArray *arr);
int strarr_copy_elements(StringArray *from_arr, StringArray *to_arr, int start_from_index, int number_of_elements);

// Printing and other cosmetic functions.
void strarr_print(StringArray *arr);

#endif