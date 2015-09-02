#pragma once

#include "utils.h"

#include "computation/description.h"

MACRO_STRUCTURE_DEFINITION(computation) {
    void* bytes;
    computation_description_ptr description;
};
