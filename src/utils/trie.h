#pragma once

#include "utils/diagnostics.h"
#include "utils/utils.h"

#include <stdint.h>

DEBUG(extern allocation_list_node_ptr allocated_trie_nodes);

MACRO_STRUCTURE_DEFINITION(trie_node)
{
    trie_node_ptr ver; // vertical adjacent
    trie_node_ptr hor; // next vertex at this level
    void* value;
    uint32_t count;
    char code;
};

typedef trie_node_ptr trie;
typedef trie_node_holder trie_holder;

trie_node_ptr trie_node_construct(char code);
void trie_node_destruct(trie_node_holder trie_node);

void  trie_insert(trie_holder root, const char* tag, void* value);
void* trie_remove(trie_holder root, const char* tag);
void* trie_check(const trie* root, const char* tag);
