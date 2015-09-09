#include "init.h"

#include "context.h"
#include "transform_description.h"
#include "types/datum.h"
#include "types/type_description.h"
#include "utils/diagnostics.h"
#include "utils/log.h"

void init(const char * logging_file_name)
{
    init_logging(logging_file_name);

    DLOG("Diagnostic mode is turned on.");

    init_types_descriptions();
    init_transforms_descriptions();
}

const int MAX_MESSAGE_SIZE = 500;

void fini()
{
#if DEBUG_MODE
    LOG("-------------------------------");

    char buffer[MAX_MESSAGE_SIZE + 1];

    if (allocated_datums != NULL) {
        sprintf(buffer, "Remaining datums at addresses: ");
        allocation_list_to_string(&allocated_datums, buffer, MAX_MESSAGE_SIZE);
        LOG("%s", buffer);
    }

    if (allocated_contexts != NULL) {
        sprintf(buffer, "Remaining contexts at addresses: ");
        allocation_list_to_string(&allocated_contexts, buffer, MAX_MESSAGE_SIZE);
        LOG("%s", buffer);
    }

#endif
}