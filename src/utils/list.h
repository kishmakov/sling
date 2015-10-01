#pragma once

#include "utils/utils.h"

// general purposes list
MACRO_STRUCTURE_DEFINITION(list_node)
{
    void * value;
    list_node_hld next;
};

typedef list_node_hld list_hld;
typedef list_node_io list_io;

void  list_insert(list_io list, void* src);
void* list_pop_front(list_io list);

