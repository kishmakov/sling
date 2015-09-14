#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

struct mind_type;
typedef uint32_t (*mind_func_ptr)(const struct mind_type* mind, context_ptr input);

MACRO_STRUCTURE_DEFINITION(mind_description)
{
    const char * input_scheme;
    const char * decision_scheme;
    const char * profile;
    uint32_t size;

    mind_func_ptr function;

    mind_description_ptr next;
};

mind_description_ptr minds_descriptions();

void init_minds_descriptions();
