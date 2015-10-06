#pragma once

#include "transforms/transform_description.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_hld allocated_transforms);

MACRO_STRUCTURE_DEFINITION(transform) {
    void* internal_data;
    transform_description_cref description;
};

transform_hld transform_construct(transform_description_cref description, void* seed);

transform_hld transform_copy(transform_cref transform);

void transform_destruct(transform_mv transform);

context_hld transform_function(transform_cref transform, context_mv input);
