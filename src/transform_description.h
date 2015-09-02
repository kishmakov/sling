#pragma once

#include "utils.h"

#include <stdint.h>

// typedef context_ptr (*compute_func_ptr)(computation_ptr computation, context_ptr input);

MACRO_STRUCTURE_DEFINITION(computation_description) {
    char * input_scheme;
    char * output_scheme;
    char * description;

    computation_description_ptr next;
};

computation_description_ptr computations_descriptions();

