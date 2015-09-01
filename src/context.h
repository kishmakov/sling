#pragma once

#include "utils.h"

#include <stdint.h>

struct computation_type;
typedef struct computation_type* computation_ptr;

struct datum_type;
typedef struct datum_type* datum_ptr;

MACRO_STRUCTURE_DEFINITION(context) {
    uint32_t computations_size;
    uint32_t data_size;

    computation_ptr* computations;
    datum_ptr* data;

};
