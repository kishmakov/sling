#pragma once

#include "context.h"

#include <stdint.h>

typedef struct {
    uint32_t from;
    uint32_t to;
} id_map_type;

typedef struct {
    uint32_t computations_maps_size;
    uint32_t data_maps_size;

    id_map_type* computations_maps;
    id_map_type* data_maps;
} transmitter_type;
typedef transmitter_type* transmitter_ptr;

void transmit(context_ptr dst, context_ptr src, transmitter_ptr transmitter);

