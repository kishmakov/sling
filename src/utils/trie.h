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
typedef trie_node_mv trie_mv;

trie_node_hld trie_node_construct(char code);
void trie_node_destruct(trie_node_mv trie_node);

trie_hld trie_insert(trie_mv root, const char* tag, void* src);
trie_hld trie_remove(trie_mv root, const char* tag, out_param dst);
void*    trie_check(trie_cref root, const char* tag);
