#include "utils.h"
#include "crypto.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#define ENCRYPT 1
#define DECRYPT 2
#define SIGN 3
#define VERIFY 4

#define UNKNOWN_ACTION -1

int get_action_form_str(char *action);

int main(int argc, char *argv[])
{
	int opt;

	char *action_str = NULL;
	char *keyfile = NULL;
	char *infile = NULL;
	char *outfile = NULL;
	char *signfile = NULL;

	while ((opt = getopt(argc, argv, ":a:k:i:o:s:")) != -1) {
		switch (opt) {
			case 'a':
				action_str = optarg;
				break;
			case 'k':
				keyfile = optarg;
				break;
			case 'i':
				infile = optarg;
				break;
			case 'o':
				outfile = optarg;
				break;
			case 's':
				signfile = optarg;
				break;
			case '?':
				printf("Unknown option %c\n", optopt);
		}
	}

	if (!action_str) {
		printf("Missing required option -a\n");
		return -1;
	}

	int action = get_action_form_str(action_str);

	printf("Action: %s (%d)\n", action_str, action);

	if (!keyfile) {
		printf("Missing required argument -k\n");
		return -1;
	}

	char *key_content;
	read_file(&key_content, keyfile);
	printf("nKey:\n%s\n\n", key_content);

	if (!infile) {
		printf("Missing required arugment -i\n");
		return -1;
	}

	char *input;
	size_t input_size = read_file(&input, infile);

	printf("Input:\n%s\n\n", input);

	if (action == DECRYPT) {
		char *result;
		crypto_decrypt(key_content, &result, input, input_size);

		printf("Decrypted content: %s\n\n", result);

		free(result);
	}

	if (input)
		free(input);
	
	if (key_content)
		free(key_content);
}

int get_action_form_str(char *action)
{
	if (strncmp(action, "encrypt", 7) == 0)
		return ENCRYPT;
	if (strncmp(action, "decrypt", 7) == 0)
		return DECRYPT;
	if (strncmp(action, "sign", 4) == 0)
		return SIGN;
	if (strncmp(action, "verify", 6) == 0)
		return VERIFY;
	
	return UNKNOWN_ACTION;
}
