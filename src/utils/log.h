#pragma once

#ifdef LOGLEVEL

#define LOGLEVEL_NONE 0
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_WARNING 2
#define LOGLEVEL_INFO 3

#include <stdio.h>

#if LOGLEVEL >= LOGLEVEL_INFO
#define LOG_INFO(format, ...) \
printf("INFO: " format "\n", ## __VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif

#if LOGLEVEL >= LOGLEVEL_WARNING
#define LOG_WARNING(format, ...) \
printf("WARNING: " format "\n", ## __VA_ARGS__)
#else
#define LOG_WARNING(format, ...)
#endif

#if LOGLEVEL >= LOGLEVEL_ERROR
#define LOG_ERROR(format, ...) \
printf("ERROR: " format "\n", ## __VA_ARGS__)
#else
#define LOG_ERROR(format, ...)
#endif

#endif