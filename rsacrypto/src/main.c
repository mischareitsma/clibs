#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rsacrypto.h"
#include "utils.h"

#define DEBUG

#define ENCRYPT 1
#define DECRYPT 2
#define SIGN 3
#define VERIFY 4

#define UNKNOWN_ACTION -1

int result = 0;

int error(char *err_msg, int err_code);

int get_action_from_str(char *action);

int main(int argc, char *argv[])
{
	int opt;

	// Variables used for options
	char *action_str = NULL;
	char *keyfile = NULL;
	char *infile = NULL;
	char *outfile = NULL;
	char *signfile = NULL;

	// Variables used to hold content of files in memory which are alloced
	char *key_content = NULL;
	char *input_content = NULL;
	char *signature_content = NULL;

	// Result of operations, use 512 bytes, supports keys up to 4096 bits
	char result[512];
	memset(result, 0, 512);

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
				break;
		}
	}

	// Required input for all actions
	if (!action_str)
		return error("Missing required argument -a", 1);

	if (!keyfile) 
		return error("Missing required argument -k", 1);

	if (!infile)
		return error("Missing required option -i", 1);


	int action = get_action_from_str(action_str);
	if (action == UNKNOWN_ACTION)
		return error("Unknown action", 2);

	read_file(&key_content, keyfile);
	if (!key_content)
		return error("Could not read keyfile", 3);

	size_t input_size = read_file(&input_content, infile);
	if (!input_content)
		return error("Could not read input file", 3);

	if (action == ENCRYPT) {
		
		if (!outfile)
			return error("Missing required option -o", 1);

		int result_size = rc_encrypt((unsigned char*)key_content,
					     (unsigned char*)input_content,
					     input_size,
					     (unsigned char*)result);
					
		write_file(result, result_size, outfile);
	}

	if (action == DECRYPT) {

		int result_size = rc_decrypt((unsigned char *)key_content,
					     (unsigned char *)input_content,
					     input_size,
					     (unsigned char *)result);

		if (!outfile)
			printf("%s\n", result);
		else
			write_file(result, result_size, outfile);
	}

	if (action == SIGN) {
		if (!outfile)
			return error("Missing required option -o", 1);

		size_t sign_size = rc_sign((unsigned char *)key_content,
					   (unsigned char *)input_content,
					   input_size, (unsigned char *)result);

		if (sign_size > 0)
			write_file(result, sign_size, outfile);

	}

	if (action == VERIFY) {

		if (!signfile)
			return error("Missing required option -s", 1);

		size_t sign_size = read_file(&signature_content, signfile);
		
		if (!signature_content)
			return error("Could not read signature file", 3);

		int verified = rc_verify((unsigned char *)key_content,
					 (unsigned char *)signature_content,
					 sign_size, (unsigned char *)input_content,
					 input_size);
		
		if (verified)
			printf("Verify OK\n");
		else
			printf("Verify failed\n");
	}

	// Cleanup, even though error cases don't do it properly.
	if (key_content)
		free(key_content);

	if (input_content)
		free(input_content);

	if (signature_content)
		free(signature_content);
	

	return 0;

}

int get_action_from_str(char *action)
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

int error(char *err_msg, int err_code)
{
	printf("%s\n", err_msg);
	return err_code;
}
