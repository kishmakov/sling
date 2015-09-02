#pragma once

#include "utils.h"

#include <stdint.h>

MACRO_STRUCTURE_DEFINITION(datum_description) {
    char * scheme;
    uint64_t size;
    datum_description_ptr next;
};

datum_description_ptr data_descriptions();

