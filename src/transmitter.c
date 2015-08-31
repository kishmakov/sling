#include "transmitter.h"

#include "context.h"

#include <assert.h>
#include <stdlib.h>

static_assert(sizeof(void*) == sizeof(computation_ptr), "Required for pointer independent code.");
static_assert(sizeof(void*) == sizeof(datum_ptr), "Required for pointer independent code.");

typedef void** void_ptr_array;

void transmit_pointes(
    uint32_t dst_size, void_ptr_array* dst,
    uint32_t src_size, void_ptr_array* src,
    uint32_t maps_size, const id_map_type* maps)
{
    uint32_t maxDstId = 0;

    for (int mapId = 0; mapId < maps_size; mapId++) {
        assert(maps[mapId].from < src_size);
        maxDstId = maxDstId < maps[mapId].to ? maps[mapId].to :  maxDstId;
    }

    if (maxDstId > dst_size)
        *dst = realloc(*dst, maxDstId + 1);

    for (int mapId = 0; mapId < maps_size; mapId++) {
        assert((*dst)[maps[mapId].to] == NULL);
        (*dst)[maps[mapId].to] = (*src)[maps[mapId].from];
        (*src)[maps[mapId].from] = NULL;
    }
}

void transmit(context_ptr dst, context_ptr src, transmitter_ptr transmitter)
{
    transmit_pointes(
        dst->computations_size, (void_ptr_array*) &(dst->computations),
        src->computations_size, (void_ptr_array*) &(src->computations),
        transmitter->computations_maps_size, transmitter->computations_maps);

    transmit_pointes(
        dst->data_size, (void_ptr_array*) &(dst->data),
        src->data_size, (void_ptr_array*) &(src->data),
        transmitter->data_maps_size, transmitter->data_maps);
}
