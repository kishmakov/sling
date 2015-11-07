#pragma once

#include "utils/diagnostics.h"
#include "utils/list.h"

// general purposes hash map

MACRO_STRUCTURE_DEFINITION(hm_node)
{
    void_hld key;
    void_hld value;
};

MACRO_STRUCTURE_DEFINITION(hm)
{
    MACRO_VECTOR_DEFINITION(baskets, list_hld);
    uint32_t inserted;
    uint32_t threshold;

    int (*equals)(void_cref key1, void_cref key2);
    uint64_t (*hash)(void_cref key);
};

hm_hld hm_construct(
    uint32_t size,
    int (*equals)(void_cref, void_cref),
    uint64_t (*hash)(void_cref));

void hm_destruct(hm_mv map);

void      hm_insert(hm_ref map, void_mv key, void_mv value);
void_hld  hm_remove(hm_ref map, void_cref key);
void_cref hm_lookup(hm_cref map, void_cref key);

// uint32_t -> uint32_t specification

extern const uint32_t HM_UINT32_UINT32_NIL;

hm_hld   hm_uint32_uint32_construct(uint32_t size);

void     hm_uint32_uint32_insert(hm_ref map, uint32_t key, uint32_t value);
uint32_t hm_uint32_uint32_remove(hm_ref map, uint32_t key);
uint32_t hm_uint32_uint32_lookup(hm_cref map, uint32_t key);

// void* -> uint32_t specification

extern const uint32_t HM_VOIDP_UINT32_NIL;

hm_hld   hm_voidp_uint32_construct(uint32_t size);

void     hm_voidp_uint32_insert(hm_ref map, void* key, uint32_t value);
uint32_t hm_voidp_uint32_remove(hm_ref map, void* key);
uint32_t hm_voidp_uint32_lookup(hm_cref map, void* key);
