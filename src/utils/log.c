#include "utils/log.h"

#include "utils/utils.h"

FILE* logging_file = NULL;

void init_logging()
{
#ifdef LOG_FILE
    logging_file = fopen(MACRO_QUOTE(LOG_FILE), "a");
#else
    logging_file = stderr;
#endif
}