#pragma once

#include <stdio.h>

extern FILE* LOGGING_FILE;

#define LOG(format, ...) \
if (LOGGING_FILE) fprintf(LOGGING_FILE, "[%s:%d]: "format"\n", __FILE__, __LINE__ , ## __VA_ARGS__)

void init_logging(const char * file_name);