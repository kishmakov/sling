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

    const char * input_scheme;
    const char * output_scheme;
    const char * profile;

    // transform methods

    transform_hld (*construct)(void);
    void (*destruct)(transform_mv transform);
    context_hld (*function)(transform_cref transform, context_mv input);
};

transform_description_cref transforms_descriptions();

