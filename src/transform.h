#pragma once

#include "transform_description.h"
#include "utils/utils.h"

MACRO_STRUCTURE_DEFINITION(transform) {
    void* bytes;
    transform_description_ptr description;
};

transform_ptr transform_construct(transform_description_cptr description);

context_ptr transform_function(transform_cptr transform, context_ptr* input_holder);
