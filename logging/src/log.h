#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <time.h>
#include <stdio.h>

enum LOG_LEVEL {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

struct log_event {
	enum LOG_LEVEL log_level;
	struct tm tm;
	char* msg_fmt;
	va_list valist;
	char *file;
	int line;
};

struct log_file {
	enum LOG_LEVEL min_log_level;
	enum LOG_LEVEL max_log_level;
	FILE *file;
};

size_t add_log_file(FILE *f, enum LOG_LEVEL min, enum LOG_LEVEL max);

void log_msg(enum LOG_LEVEL log_level, char *file, int line, char *msg_fmt, ...);
void log_msg_to_file(FILE *f,enum LOG_LEVEL log_level, char *file, int line, char *msg_fmt, ...);

void log_event(struct log_event *event);
void log_event_to_file(FILE *f, struct log_event *event);


#define log_trace(...) log_msg(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_msg(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_msg(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_msg(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_msg(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_msg(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#define log_trace_to_file(f, ...) log_msg_to_file(f, LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug_to_file(f, ...) log_msg_to_file(f, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info_to_file(f, ...)  log_msg_to_file(f, LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_to_file(f, ...)  log_msg_to_file(f, LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error_to_file(f, ...) log_msg_to_file(f, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal_to_file(f, ...) log_msg_to_file(f, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif /* __LOG_H__ */