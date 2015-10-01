#pragma once

#include "utils/diagnostics.h"
#include "utils/utils.h"

#include <stdint.h>

DEBUG(extern allocation_list_hld allocated_trie_nodes);

MACRO_STRUCTURE_DEFINITION(trie_node)
{
    trie_node_hld ver; // vertical adjacent
    trie_node_hld hor; // next vertex at this level
    void* value;
    uint32_t count;
    char code;
};

typedef trie_node_hld trie_hld;
typedef trie_node_cref trie_cref;
typedef trie_node_io trie_io;

trie_node_hld trie_node_construct(char code);
void trie_node_destruct(trie_node_mv trie_node);

void  trie_insert(trie_io root, const char* tag, void* src);
void* trie_remove(trie_io root, const char* tag);
void* trie_check(trie_cref root, const char* tag);
