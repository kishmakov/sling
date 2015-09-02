#pragma once

#include "context.h"
#include "utils.h"

#include <stdint.h>

typedef struct {
    uint32_t from;
    uint32_t to;
} id_map_type;

MACRO_STRUCTURE_DEFINITION(transmitter) {
    uint32_t transforms_maps_size;
    uint32_t data_maps_size;

    id_map_type* transforms_maps;
    id_map_type* data_maps;
};

void transmit(const transmitter_type* transmitter, context_ptr dst, context_ptr src);

