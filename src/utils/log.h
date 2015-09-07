#pragma once

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3

#include <stdio.h>

extern FILE* logging_file;

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(format, ...) \
fprintf(logging_file, "INFO: " format "\n", ## __VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOG_WARNING(format, ...) \
fprintf(logging_file, "WARNING: " format "\n", ## __VA_ARGS__)
#else
#define LOG_WARNING(format, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(format, ...) \
fprintf(logging_file, "ERROR: " format "\n", ## __VA_ARGS__)
#else
#define LOG_ERROR(format, ...)
#endif

void init_logging();