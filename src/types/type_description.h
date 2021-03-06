#pragma once

#include "utils/utils.h"

#include <stdint.h>

void init_types_descriptions();

MACRO_STRUCTURE_DEFINITION(type_description)
{
    char * scheme;
    uint32_t size;
    type_description_cref next;
};

type_description_cref types_descriptions();
