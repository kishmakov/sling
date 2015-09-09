#pragma once

#include "utils/utils.h"

#include <stdint.h>

MACRO_STRUCTURE_DEFINITION(type_description)
{
    char * scheme;
    uint32_t size;
    type_description_ptr next;
};

type_description_ptr types_descriptions();

void init_types_descriptions();