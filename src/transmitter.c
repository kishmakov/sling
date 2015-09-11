#include "transmitter.h"

#include "context.h"
#include "utils/utils.h"

#include <assert.h>
#include <stdlib.h>

transmitter_ptr transmitter_create(uint32_t data_size, uint32_t transforms_size)
{
    transmitter_ptr result = malloc(sizeof(transmitter_type));
    MACRO_VECTOR_ALLOCATE(result->data_maps, id_map_type, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms_maps, id_map_type, transforms_size);
    return result;
}

void transmitter_delete(transmitter_ptr* transmitter_holder)
{
    free((*transmitter_holder)->data_maps);
    free((*transmitter_holder)->transforms_maps);
    free(*transmitter_holder);
    *transmitter_holder = NULL;
};

#if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 5)
static_assert(sizeof(void*) == sizeof(transform_ptr), "Required for pointer independent code.");
static_assert(sizeof(void*) == sizeof(datum_ptr), "Required for pointer independent code.");
#endif

typedef void** void_ptr_array;

void transmit_pointes(
    uint32_t maps_size, const id_map_type* maps,
    uint32_t dst_size, void_ptr_array* dst,
    uint32_t src_size, void_ptr_array* src)
{
    uint32_t maxDstId = 0;

    for (int mapId = 0; mapId < maps_size; mapId++) {
        assert(maps[mapId].from < src_size);
        maxDstId = MACRO_MIN(maxDstId, maps[mapId].to);
    }

    if (maxDstId > dst_size)
        *dst = realloc(*dst, maxDstId + 1);

    for (int mapId = 0; mapId < maps_size; mapId++) {
        assert((*dst)[maps[mapId].to] == NULL);
        (*dst)[maps[mapId].to] = (*src)[maps[mapId].from];
        (*src)[maps[mapId].from] = NULL;
    }
}

void transmit(transmitter_cptr transmitter, context_ptr dst, context_ptr src)
{
    transmit_pointes(
        transmitter->data_maps_size, transmitter->data_maps,
        dst->data_size, (void_ptr_array*) &(dst->data),
        src->data_size, (void_ptr_array*) &(src->data));

    transmit_pointes(
        transmitter->transforms_maps_size, transmitter->transforms_maps,
        dst->transforms_size, (void_ptr_array*) &(dst->transforms),
        src->transforms_size, (void_ptr_array*) &(src->transforms));
}
