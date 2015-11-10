#pragma once

#include "utils/utils.h"

// general purposes list
MACRO_STRUCTURE_DEFINITION(list_node)
{
    void_hld value;
    list_node_hld next;
};

typedef list_node_hld list_hld;
typedef list_node_io list_io;
typedef list_node_mv list_mv;

void     list_insert(list_io list, void_mv list_ptr);
void_hld list_pop_front(list_io list);
void     list_append(list_io dst, list_mv addition);

