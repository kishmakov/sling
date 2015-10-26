#include "utils/hash_map.h"

#include <assert.h>
#include <stdlib.h>

static const double load_factor = 0.75;

hash_map_hld hash_map_construct(
    uint32_t size,
    int (*equals)(void_cref, void_cref),
    uint64_t (*hash)(void_cref))
{
    assert(equals != NULL);
    assert(hash != NULL);

    hash_map_hld result = malloc(sizeof(hash_map_type));

    MACRO_VECTOR_ALLOCATE(result->baskets, list_hld, size);

    result->inserted = 0;
    result->threshold = (uint32_t) load_factor * size;

    result->equals = equals;
    result->hash = hash;

    return result;
}

hash_map_hld hash_map_construct_default(uint32_t size)
{
    return hash_map_construct(size, NULL, NULL);
}

static void hash_map_resize(hash_map_ref map, uint32_t new_size)
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

    while (elements != NULL) {
        hash_map_node_hld node = (hash_map_node_hld) list_pop_front(&elements);
        hash_map_insert(map, &(node->key), &(node->value));
        assert(node->key == NULL);
        assert(node->value == NULL);
        free(node);
        node = NULL;
    }
}

static void_hld basket_remove(
    list_io list,
    void_cref key,
    int (*equals)(void_cref, void_cref))
{
    assert(list != NULL);
    assert(key != NULL);
    assert(equals != NULL);

    for (list_node_hld* cur = list; *cur != NULL; cur = &((*cur)->next)) {
        hash_map_node_hld node = (hash_map_node_hld) (*cur)->value;
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

void hash_map_insert(hash_map_ref map, void_mv key, void_mv value)
{
    assert(map != NULL);
    assert(key != NULL && *key != NULL);
    assert(value != NULL && *value != NULL);

    if (map->inserted == map->threshold)
        hash_map_resize(map, 2 * map->baskets_size);

    uint32_t basket_num = map->hash(*key) % map->baskets_size;
    assert(NULL == basket_remove(&(map->baskets[basket_num]), *key, map->equals));

    hash_map_node_hld node = malloc(sizeof(hash_map_node_type));
    node->key = *key;
    *key = NULL;
    node->value = *value;
    *value = NULL;

    list_insert(&(map->baskets[basket_num]), (void_mv) &node);
    assert(node == NULL);
}

void_hld hash_map_remove(hash_map_ref map, void_cref key)
{
    assert(map != NULL);
    assert(key != NULL);

    uint32_t basket_num = map->hash(key) % map->baskets_size;
    return basket_remove(&(map->baskets[basket_num]), key, map->equals);
}
