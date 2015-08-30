#pragma once

#include <stdint.h>

typedef computation_type* computation_ptr;
typedef datum_type* datum_ptr;

typedef struct {
    size_t computations_size;
    computation_ptr* computations;

    size_t data_size;
    datum_ptr* data;

} context_type;
typedef context_type* context_ptr;

typedef struct {
    uint32_t from;
    uint32_t to;
} id_map_type;

typedef struct {
    id_map_type* computations_maps;
    id_map_type* data_maps;
} transmitter_type;
typedef transmitter_type* transmitter_ptr;

void transmit(transmitter_ptr map, context_ptr donor, context_ptr recepient);

