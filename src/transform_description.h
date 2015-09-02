#pragma once

#include "context.h"
#include "utils.h"

#include <stdint.h>

struct trasform_type;
typedef context_ptr (*transform_func_ptr)(struct trasform_type transform, context_ptr input);

MACRO_STRUCTURE_DEFINITION(transform_description) {
    char * input_scheme;
    char * output_scheme;
    char * profile;
    transform_func_ptr function;

    transform_description_ptr next;
};

transform_description_ptr transform_descriptions();

