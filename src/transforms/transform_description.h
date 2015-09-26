#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

void init_transforms_descriptions();

struct transform_type;
typedef struct transform_type* transform_ptr;
typedef transform_ptr* transform_holder;
typedef const struct transform_type* transform_cptr;

MACRO_STRUCTURE_DEFINITION(transform_description)
{
    transform_description_cptr next;

    const char * input_scheme;
    const char * output_scheme;
    const char * profile;

    // transform methods

    transform_ptr (*construct)(void);
    void (*destruct)(transform_holder transform);
    context_ptr (*function)(transform_cptr transform, context_holder input);
};

transform_description_ptr transforms_descriptions();

