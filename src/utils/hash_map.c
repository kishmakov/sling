#include "utils/hash_map.h"

#include <assert.h>
#include <stdlib.h>

static const double load_factor = 0.75;

hm_hld hm_construct(
    uint32_t size,
    int (*equals)(void_cref, void_cref),
    uint64_t (*hash)(void_cref))
{
    assert(equals != NULL);
    assert(hash != NULL);

    hm_hld result = malloc(sizeof(hm_type));

    size = MACRO_MAX(size, 8);

    MACRO_VECTOR_ALLOCATE(result->baskets, list_hld, size);

    result->inserted = 0;
    result->threshold = (uint32_t) (load_factor * size);

    result->equals = equals;
    result->hash = hash;

    return result;
}

void hm_destuct(hm_mv map_ptr)
{
    hm_ref map = *map_ptr;

    for (uint32_t id = 0; id < map->baskets_size; id++) {
        while (map->baskets[id] != NULL) {
            hm_node_hld node = (hm_node_hld) list_pop_front(&map->baskets[id]);
            free(node->key);
            free(node->value);
            free(node);
        }
    }
    free(map->baskets);
    free(*map_ptr);
    *map_ptr = NULL;
}

static void hm_resize(hm_ref map, uint32_t new_size)
{
    list_hld elements = NULL;

    for (uint32_t id = 0; id < map->baskets_size; id++) {
        list_append(&(map->baskets[id]), &elements);
        assert(elements == NULL);
        elements = map->baskets[id];
        map->baskets[id] = NULL;
    }

    MACRO_VECTOR_RESIZE(map->baskets, list_hld, new_size);
    map->threshold = (uint32_t) load_factor * new_size;
    map->inserted = 0;

    while (elements != NULL) {
        hm_node_hld node = (hm_node_hld) list_pop_front(&elements);
        hm_insert(map, &(node->key), &(node->value));
        assert(node->key == NULL && node->value == NULL);
        free(node);
        node = NULL;
    }
}

static void_hld basket_remove(
    list_io list,
    void_cref key,
    int (*equals)(void_cref, void_cref))
{
    assert(list != NULL && key != NULL && equals != NULL);

    for (list_node_hld* cur = list; *cur != NULL; cur = &((*cur)->next)) {
        hm_node_hld node = (hm_node_hld) (*cur)->value;
        if (!equals(key, node->key))
            continue;

        list_node_hld next = (*cur)->next;

        void_hld result = node->value;
        free(node->key);
        free((*cur)->value);
        free(*cur);

        *cur = next;

        return result;
    }

    return NULL;
}

static void_cref basket_lookup(
    list_node_cref list,
    void_cref key,
    int (*equals)(void_cref, void_cref))
{
    assert(key != NULL && equals != NULL);

    for (list_node_cref cur = list; cur != NULL; cur = cur->next) {
        hm_node_hld node = (hm_node_hld) cur->value;
        if (equals(key, node->key))
            return node->value;
    }

    return NULL;
}

void hm_insert(hm_ref map, void_mv key, void_mv value)
{
    assert(map != NULL);
    assert(key != NULL && *key != NULL);
    assert(value != NULL && *value != NULL);

    if (map->inserted >= map->threshold)
        hm_resize(map, 2 * map->baskets_size);

    uint32_t basket_num = map->hash(*key) % map->baskets_size;
    assert(NULL == basket_remove(&(map->baskets[basket_num]), *key, map->equals));

    hm_node_hld node = malloc(sizeof(hm_node_type));
    node->key = *key;
    *key = NULL;
    node->value = *value;
    *value = NULL;

    list_insert(&(map->baskets[basket_num]), (void_mv) &node);
    assert(node == NULL);
}

void_hld hm_remove(hm_ref map, void_cref key)
{
    assert(map != NULL);
    assert(key != NULL);

    if (map->baskets_size == 0)
        return NULL;

    uint32_t basket_num = map->hash(key) % map->baskets_size;
    return basket_remove(&(map->baskets[basket_num]), key, map->equals);
}

void_cref hm_lookup(hm_cref map, void_cref key)
{
    assert(map != NULL);
    assert(key != NULL);

    if (map->baskets_size == 0)
        return NULL;

    uint32_t basket_num = map->hash(key) % map->baskets_size;
    return basket_lookup(map->baskets[basket_num], key, map->equals);
}

// uint32_t -> uint32_t specification

const uint32_t HM_UINT32_UINT32_NIL = 0xFFFFFFFFu;

static int equals_uint32(void_cref key1, void_cref key2)
{
    return ptr_to_uint32(key1) == ptr_to_uint32(key2);
}

static uint64_t hash_uint32(void_cref key)
{
    return (uint64_t) ptr_to_uint32(key);
}

hm_hld hm_uint32_uint32_construct(uint32_t size)
{
    return hm_construct(size, &equals_uint32, &hash_uint32);
}

void hm_uint32_uint32_insert(hm_ref map, uint32_t key, uint32_t value)
{
    assert(map != NULL);

    void_hld key_ptr = uint32_to_ptr(key);
    void_hld value_ptr = uint32_to_ptr(value);
    hm_insert(map, &key_ptr, &value_ptr);
    assert(key_ptr == NULL && value_ptr == NULL);
}

uint32_t hm_uint32_uint32_remove(hm_ref map, uint32_t key)
{
    assert(map != NULL);

    void_hld key_ptr = uint32_to_ptr(key);
    void_hld result_ptr = hm_remove(map, key_ptr);
    free(key_ptr);

    if (result_ptr != NULL) {
        uint32_t result = ptr_to_uint32(result_ptr);
        free(result_ptr);
        return result;
    }

    return HM_UINT32_UINT32_NIL;
}

uint32_t hm_uint32_uint32_lookup(hm_cref map, uint32_t key)
{
    assert(map != NULL);

    void_hld key_ptr = uint32_to_ptr(key);
    void_cref result_ptr = hm_lookup(map, key_ptr);
    free(key_ptr);

    return result_ptr != NULL ? ptr_to_uint32(result_ptr) : HM_UINT32_UINT32_NIL;
}

// void* -> uint32_t specification

// void     hm_voidp_uint32_insert(hm_ref map, void* key, uint32_t value);
// uint32_t hm_voidp_uint32_remove(hm_ref map, void* key);
// uint32_t hm_voidp_uint32_lookup(hm_cref map, void* key);
