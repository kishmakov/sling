#pragma once

#include "utils/utils.h"

// list for stroing pointers on allocated objects
MACRO_STRUCTURE_DEFINITION(allocation_list_node)
{
    const void * allocated_address;
    allocation_list_node_hld next;
};

typedef allocation_list_node_hld allocation_list;
typedef allocation_list_node_cref allocation_list_cref;
typedef allocation_list_node_mv allocation_list_mv;

allocation_list allocation_list_insert(allocation_list_mv list, const void* address);
allocation_list allocation_list_remove(allocation_list_mv list, const void* address);
void allocation_list_to_string(allocation_list_cref list, char* buffer, int max_size);
