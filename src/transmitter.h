#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

typedef struct {
    uint32_t from;
    uint32_t to;
} id_map_type;

MACRO_STRUCTURE_DEFINITION(transmitter) {
    MACRO_VECTOR_DEFINITION(data_maps, id_map_type);
    MACRO_VECTOR_DEFINITION(transforms_maps, id_map_type);
};

transmitter_hld transmitter_construct(uint32_t data_size, uint32_t transforms_size);

void transmitter_destruct(transmitter_mv transmitter);

void transmit(transmitter_cref transmitter, context_ref dst, context_ref src);

void transmit_copy(transmitter_cref transmitter, context_ref dst, context_ref src);

