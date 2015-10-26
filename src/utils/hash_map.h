#pragma once

#include "utils/diagnostics.h"
#include "utils/list.h"

// general purposes hash map

MACRO_STRUCTURE_DEFINITION(hash_map_node)
{
    void_hld key;
    void_hld value;
};

MACRO_STRUCTURE_DEFINITION(hash_map)
{
    MACRO_VECTOR_DEFINITION(baskets, list_hld);
    uint32_t inserted;
    uint32_t threshold;

    int (*equals)(void_cref key1, void_cref key2);
    uint64_t (*hash)(void_cref key);
};

hash_map_hld hash_map_construct(
    uint32_t size,
    int (*equals)(void_cref, void_cref),
    uint64_t (*hash)(void_cref));
hash_map_hld hash_map_construct_default(uint32_t size);

void     hash_map_insert(hash_map_ref map, void_mv key, void_mv value);
void_hld hash_map_remove(hash_map_ref map, void_cref key);
