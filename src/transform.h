#pragma once

#include "transform_description.h"
#include "utils/utils.h"

MACRO_STRUCTURE_DEFINITION(transform) {
    void* bytes;
    transform_description_ptr description;
};
