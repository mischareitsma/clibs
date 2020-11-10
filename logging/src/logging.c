#include "ansi.h"
#include "logging.h"

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#define MAX_LOG_FILES 10

static size_t n_log_files = 0;
static struct log_file log_files[MAX_LOG_FILES];

static const char *log_level_string[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *log_level_color[] = {
	ANSI_FG_BLACK, ANSI_FG_CYAN, ANSI_FG_GREEN, ANSI_FG_YELLOW,
	ANSI_FG_RED, ANSI_FG_MAGENTA
};

size_t add_log_file(FILE *file, enum LOG_LEVEL min, enum LOG_LEVEL max)
{
	// Max reached
	if (n_log_files == MAX_LOG_FILES - 1)
		return 0;

	log_files[n_log_files].file = file;
	log_files[n_log_files].min_log_level = min;
	log_files[n_log_files].max_log_level = max;
	n_log_files++;
	return n_log_files;
	
}

void log_msg(enum LOG_LEVEL log_level, char *file, int line, char *msg_fmt, ...)
{
	struct log_event event;
	event.log_level = log_level;
	event.file = file;
	event.line = line;
	event.msg_fmt = msg_fmt;

	va_start(event.valist, msg_fmt);

	time_t t = time(NULL);
	event.tm =  *localtime(&t);

	log_event(&event);
	va_end(event.valist);
}

void log_event(struct log_event *event)
{
	for(int i = 0; i < n_log_files; i++) {
		struct log_file lf = log_files[i];
		if (event->log_level < lf.min_log_level)
			continue;
		if (event->log_level > lf.max_log_level)
			continue;
		
		log_event_to_file(lf.file, event);
	}
}

void log_msg_to_file(FILE *f,enum LOG_LEVEL log_level, char *file, int line, char *msg_fmt, ...)
{
	struct log_event event;
	event.log_level = log_level;
	event.file = file;
	event.line = line;
	event.msg_fmt = msg_fmt;

	va_start(event.valist, msg_fmt);

	time_t t = time(NULL);
	event.tm =  *localtime(&t);

	log_event_to_file(f, &event);
	va_end(event.valist);
}


void log_event_to_file(FILE *f, struct log_event *event)
{
	char dt[20];
	strftime(dt, 19, "%Y-%m-%d %H:%M:%S", &event->tm);
	dt[19] = '\0';
	fprintf(f, "%s - %s%-5s%s - %s:%d - ", dt,
		log_level_color[event->log_level],
		log_level_string[event->log_level],
		ANSI_RESET, event->file, event->line);

	// Use copy of valist, as the event can be logged in various files.
	va_list valist;
	va_copy(valist, event->valist);
	vfprintf(f, event->msg_fmt, valist);
	va_end(valist);

	fprintf(f, "\n");
	fflush(f);

}