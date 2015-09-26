#pragma once

#include "transforms/transform_description.h"
#include "utils/utils.h"

DEBUG(extern allocation_list allocated_transforms);

MACRO_STRUCTURE_DEFINITION(transform) {
    void* bytes;
    transform_description_ptr description;
};

transform_ptr transform_construct(transform_description_cptr description);

void transform_destruct(transform_holder transform);

context_ptr transform_function(transform_cptr transform, context_holder input);
