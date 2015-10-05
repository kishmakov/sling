#include "transmitter.h"

#include "context.h"
#include "transforms/transform.h"
#include "types/datum.h"
#include "utils/utils.h"

#include <assert.h>
#include <stdlib.h>

DEBUG(allocation_list_hld allocated_transmitters = NULL);

transmitter_hld transmitter_construct(uint32_t data_size, uint32_t transforms_size)
{
    transmitter_hld result = malloc(sizeof(transmitter_type));
    MACRO_VECTOR_ALLOCATE(result->data_maps, id_map_type, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms_maps, id_map_type, transforms_size);
    DEBUG(allocation_list_insert(&allocated_transmitters, result));

    return result;
}

transmitter_hld transmitter_copy(transmitter_cref transmitter)
{
    assert(transmitter != NULL);
    transmitter_hld result = malloc(sizeof(transmitter_type));
    MACRO_VECTOR_ALLOCATE(result->data_maps, id_map_type, transmitter->data_maps_size);
    MACRO_VECTOR_ALLOCATE(result->transforms_maps, id_map_type, transmitter->transforms_maps_size);

    for (uint32_t id = 0; id < result->data_maps_size; id++)
        result->data_maps[id] = transmitter->data_maps[id];

    for (uint32_t id = 0; id < result->transforms_maps_size; id++)
        result->transforms_maps[id] = transmitter->transforms_maps[id];

    return result;
}

void transmitter_destruct(transmitter_mv transmitter)
{
    assert(transmitter != NULL);
    assert(*transmitter != NULL);
    DEBUG(allocation_list_remove(&allocated_transmitters, *transmitter));
    free((*transmitter)->data_maps);
    free((*transmitter)->transforms_maps);
    free(*transmitter);
    *transmitter = NULL;
};

#if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 5)
static_assert(sizeof(void*) == sizeof(transform_hld), "Required for pointer independent code.");
static_assert(sizeof(void*) == sizeof(datum_hld), "Required for pointer independent code.");
#endif

id_map_type maximal_indices(uint32_t maps_size, const id_map_type* maps)
{
    assert(maps != NULL);

    id_map_type result = {.from = 0, .to = 0};

    for (uint32_t id = 0; id < maps_size; id++) {
        result.from = MACRO_MAX(result.from, maps[id].from);
        result.to   = MACRO_MAX(result.to,   maps[id].to);
    }

    return result;
}

void transmit_move(transmitter_cref transmitter, context_ref dst, context_ref src)
{
    assert(transmitter != NULL);
    assert(dst != NULL);
    assert(src != NULL);

    id_map_type data_indices = maximal_indices(transmitter->data_maps_size,
        transmitter->data_maps);

    assert(src->data_size > data_indices.from);
    MACRO_VECTOR_RESIZE(dst->data, id_map_type, data_indices.to + 1);

    for (uint32_t id = 0; id < transmitter->data_maps_size; id++) {
        id_map_type map = transmitter->data_maps[id];
        dst->data[map.to] = src->data[map.from];
        src->data[map.from] = NULL;
    }

    id_map_type transforms_indices = maximal_indices(transmitter->transforms_maps_size,
        transmitter->transforms_maps);

    assert(src->transforms_size > transforms_indices.from);
    MACRO_VECTOR_RESIZE(dst->transforms, id_map_type, transforms_indices.to + 1);

    for (uint32_t id = 0; id < transmitter->transforms_maps_size; id++) {
        id_map_type map = transmitter->transforms_maps[id];
        dst->transforms[map.to] = src->transforms[map.from];
        src->transforms[map.from] = NULL;
    }
}

void transmit_copy(transmitter_cref transmitter, context_ref dst, context_ref src)
{
    assert(transmitter != NULL);
    id_map_type data_indices = maximal_indices(transmitter->data_maps_size,
        transmitter->data_maps);

    assert(src->data_size > data_indices.from);
    MACRO_VECTOR_RESIZE(dst->data, id_map_type, data_indices.to + 1);

    for (uint32_t id = 0; id < transmitter->data_maps_size; id++) {
        id_map_type map = transmitter->data_maps[id];
        dst->data[map.to] = datum_copy(src->data[map.from]);
    }

    id_map_type transforms_indices = maximal_indices(transmitter->transforms_maps_size,
        transmitter->transforms_maps);

    assert(src->transforms_size > transforms_indices.from);
    MACRO_VECTOR_RESIZE(dst->transforms, id_map_type, transforms_indices.to + 1);

    for (uint32_t id = 0; id < transmitter->transforms_maps_size; id++) {
        id_map_type map = transmitter->transforms_maps[id];
        transform_cref transform = (transform_cref) src->transforms[map.from];
        dst->transforms[map.to] = (void*) transform->description->copy(transform);
    }
}
