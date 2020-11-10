#include <stdio.h>
#include <stdarg.h>
#include "log.h"


void run_log_msg_test();

int main()
{
	printf("Starting test\n");
	add_log_file(stdout, LOG_TRACE, LOG_FATAL);
	add_log_file(stderr, LOG_ERROR, LOG_FATAL);
	FILE *f = fopen("example.log", "a");
	add_log_file(f, LOG_TRACE, LOG_FATAL);
	run_log_msg_test();
	printf("Ending test\n");
	return 0;
}

void run_log_msg_test()
{
	log_trace("My trace message, with arg: %s", "trace_arg");
	log_debug("My debug message, with arg: %s", "debug_arg");
	log_info("My info message, with arg: %s", "info_arg");
	log_warn("My warn message, with arg: %s", "warn_arg");
	log_error("My error message, with arg: %s", "error_arg");
	log_fatal("My fatal message, with arg: %s", "fatal_arg");

	log_info_to_file(stdout, "This message should only be in stdout, with arg: %s", "exclusive");
}
