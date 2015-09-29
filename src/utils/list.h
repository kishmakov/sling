#pragma once

#include "utils/utils.h"

// general purposes list
MACRO_STRUCTURE_DEFINITION(list_node)
{
    void * value;
    list_node_hld next;
};

typedef list_node_hld list;
typedef list_node_mv list_mv;

list list_insert(list_mv list, void* value);
list list_pop_front(list_mv list, out_param value);

