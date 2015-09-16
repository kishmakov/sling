#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

void init_transforms_descriptions();

struct transform_type;
typedef struct transform_type* transform_ptr;
typedef const struct transform_type* transform_cptr;

typedef transform_ptr (*transform_constructor_ptr)(void);
typedef void (*transform_destructor_ptr)(transform_ptr* transform_holder);
typedef context_ptr (*transform_function_ptr)(transform_cptr transform, context_ptr* input_holder);

MACRO_STRUCTURE_DEFINITION(transform_description)
{
    transform_description_cptr next;

    const char * input_scheme;
    const char * output_scheme;
    const char * profile;

    // transform frame methods

    transform_constructor_ptr construct;
    transform_destructor_ptr destruct;
    transform_function_ptr function;

};

transform_description_ptr transforms_descriptions();

