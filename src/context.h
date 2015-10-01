#pragma once

#include "utils/diagnostics.h"
#include "utils/utils.h"

#include <stdint.h>

DEBUG(extern allocation_list_hld allocated_contexts);

struct transform_type;
typedef struct transform_type* transform_hld;

struct datum_type;
typedef struct datum_type* datum_hld;

MACRO_STRUCTURE_DEFINITION(context)
{
    MACRO_VECTOR_DEFINITION(data, datum_hld);
    MACRO_VECTOR_DEFINITION(transforms, transform_hld);
};

context_hld context_construct(uint32_t data_size, uint32_t transforms_size);

void context_destruct(context_mv context);
