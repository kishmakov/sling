#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

struct trasform_type;
typedef struct trasform_type* trasform_ptr;
typedef const struct trasform_type* trasform_cptr;

typedef context_ptr (*transform_func_ptr)(trasform_cptr transform, context_ptr input);
typedef transform_ptr (*transform_constructor_ptr)(void);

MACRO_STRUCTURE_DEFINITION(transform_description)
{
    transform_description_cptr next;

    const char * input_scheme;
    const char * output_scheme;
    const char * profile;

    // methods

    transform_func_ptr function;
    transform_constructor_ptr construct;

};

transform_description_ptr transforms_descriptions();

void init_transforms_descriptions();

