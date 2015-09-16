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

transmitter_ptr transmitter_construct(uint32_t data_size, uint32_t transforms_size);

void transmitter_destruct(transmitter_ptr* transmitter_holder);

void transmit(transmitter_cptr transmitter, context_ptr dst, context_ptr src);

