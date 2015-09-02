#pragma once

#include "utils.h"

#include <stdint.h>

struct transform_type;
typedef struct transform_type* transform_ptr;

struct datum_type;
typedef struct datum_type* datum_ptr;

MACRO_STRUCTURE_DEFINITION(context) {
    uint32_t data_size;
    uint32_t transforms_size;

    datum_ptr* data;
    transform_ptr* transforms;
};

context_ptr create_context(uint32_t data_size, uint32_t transforms_size);
