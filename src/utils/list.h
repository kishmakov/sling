#pragma once

#include "utils/utils.h"

// general purposes list
MACRO_STRUCTURE_DEFINITION(list_node)
{
    void * value;
    list_node_ptr next;
};

typedef list_node_ptr list;

void list_insert(list* list_holder, void* value);
void* list_pop_front(list* list_holder);

