#pragma once

#include "utils/diagnostics.h"
#include "utils/utils.h"

#include <stdint.h>

DEBUG(extern allocation_list_hld allocated_trie_nodes);

typedef void (*value_destructor)(void_mv value_ptr);
typedef void_hld (*value_copier)(void_cref value);

MACRO_STRUCTURE_DEFINITION(trie_node)
{
    trie_node_hld ver; // vertical adjacent
    trie_node_hld hor; // next vertex at this level
    void_hld value;
    uint32_t count;
    char code;
};

trie_node_hld trie_node_construct(char code);
void          trie_node_destruct(trie_node_mv node_ptr, value_destructor destructor);
trie_node_hld trie_node_copy(trie_node_cref node, value_copier copier);

MACRO_STRUCTURE_DEFINITION(trie)
{
    trie_node_hld root;
    uint32_t size;
};

trie_hld trie_construct();
void     trie_destruct(trie_mv trie_ptr, value_destructor destructor);
trie_hld trie_copy(trie_cref trie, value_copier copier);

void     trie_insert(trie_ref trie, const char* tag, void_hld value);
void_hld trie_remove(trie_ref trie, const char* tag);
void_ref trie_check(trie_cref trie, const char* tag);
