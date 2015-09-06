#pragma once

#ifdef LOGLEVEL

#define LOGLEVEL_NONE 0
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_WARNING 2
#define LOGLEVEL_INFO 3

#include <stdio.h>

#if LOGLEVEL >= LOGLEVEL_INFO
#define LOG_INFO(format, ...) \
printf(format "\n", ## __VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif

#endif