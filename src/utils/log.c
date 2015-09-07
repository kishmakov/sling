#include "utils/log.h"

#include "utils/diagnostics.h"

FILE* LOGGING_FILE = NULL;

void init_logging(const char * logging_file_name)
{
    if (logging_file_name != NULL)
        LOGGING_FILE = fopen(logging_file_name, "a");
}