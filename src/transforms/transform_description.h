#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

void init_transforms_descriptions();

struct transform_type;
typedef struct transform_type* transform_hld;
typedef struct transform_type** transform_mv;
typedef const struct transform_type* transform_cref;

MACRO_STRUCTURE_DEFINITION(transform_description)
{
    transform_description_cref next;

    // transform methods

    transform_hld (*construct)(void* seed);
    transform_hld (*copy)(transform_cref transform);
    void (*destruct)(transform_mv transform);
    context_hld (*function)(transform_cref transform, context_mv input);

    const char* (*input_scheme)(transform_cref transform);
    const char* (*output_scheme)(transform_cref transform);
    const char* (*profile)(transform_cref transform);
};

transform_description_cref transforms_descriptions();

