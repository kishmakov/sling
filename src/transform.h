#pragma once

#include "utils.h"

#include "transform_description.h"

MACRO_STRUCTURE_DEFINITION(transform) {
    void* bytes;
    transform_description_ptr description;
};
