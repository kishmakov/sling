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

trie_node_ptr trie_node_construct(char code);
void trie_node_destruct(trie_node_ptr* trie_node_holder);

void  trie_insert(trie* trie_holder, const char* tag, void* value);
void* trie_remove(trie* trie_holder, const char* tag);
void* trie_check(const trie* trie_holder, const char* tag);
