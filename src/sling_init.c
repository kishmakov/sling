#include "sling_init.h"

#include "context.h"
#include "transform_description.h"
#include "types/datum.h"
#include "types/type_description.h"
#include "utils/diagnostics.h"
#include "utils/log.h"
#include "utils/trie.h"

#include <string.h>

void sling_init(const char * logging_file_name)
{
    init_logging(logging_file_name);

    DLOG("Diagnostic mode is turned on.");

    init_types_descriptions();
    init_transforms_descriptions();
}

void allocation_balance(allocation_list allocated_objects, const char * msg)
{
    static const int MAX_MESSAGE_SIZE = 500;
    static char buffer[MAX_MESSAGE_SIZE + 1];

    if (allocated_objects == NULL)
        return;

    sprintf(buffer, "Remaining %s  objects at addresses: ", msg);
    allocation_list_to_string(&allocated_objects, buffer, MAX_MESSAGE_SIZE);
    LOG("%s", buffer);
}

void sling_fini()
{
#if DEBUG_MODE
    LOG("-------------------------------");

    allocation_balance(allocated_datums, "datum");
    allocation_balance(allocated_contexts, "context");
    allocation_balance(allocated_trie_nodes, "trie_node");
#endif
}
