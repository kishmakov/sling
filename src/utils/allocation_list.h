#pragma once

#include "utils/utils.h"

// list for stroing pointers on allocated objects
MACRO_STRUCTURE_DEFINITION(allocation_list_node)
{
    const void * allocated_address;
    allocation_list_node_ptr next;
};

void allocation_list_insert(allocation_list_node_ptr* head_holder, const void* address);
void allocation_list_remove(allocation_list_node_ptr* head_holder, const void* address);
void allocation_list_to_string(allocation_list_node_cptr head_holder, char* buffer, int max_size);
