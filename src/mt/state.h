#pragma once

#include "transforms/transform_description.h"
#include "transmitter.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_hld allocated_states);


MACRO_STRUCTURE_DEFINITION(state) {
    struct step {
        const char* transform_profile;
        transmitter_hld download;
        transmitter_hld upload;
    };

    MACRO_VECTOR_DEFINITION(steps, struct step);

    transmitter_hld download;
    const char* mind_profile;
};

