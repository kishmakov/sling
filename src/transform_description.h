#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

struct trasform_type;
typedef context_ptr (*transform_func_ptr)(struct trasform_type transform, context_ptr input);

MACRO_STRUCTURE_DEFINITION(transform_description)
{
    const char * input_scheme;
    const char * output_scheme;
    const char * profile;
    transform_func_ptr function;

    transform_description_cptr next;
};

transform_description_ptr transforms_descriptions();

void init_transforms_descriptions();

