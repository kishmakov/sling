#pragma once

#include "transmitter.h"
#include "utils/utils.h"

DEBUG(extern allocation_list allocated_states);


MACRO_STRUCTURE_DEFINITION(state) {
    struct step {
        const char* transform_profile;
        transmitter_ptr download;
        transmitter_ptr upload;
    };

    MACRO_VECTOR_DEFINITION(steps, struct step);

    transmitter_ptr download;
    const char* mind_profile;

    transform_description_ptr description;
};

