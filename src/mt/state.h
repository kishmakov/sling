#pragma once

#include "transforms/transform_description.h"
#include "transmitter.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_hld allocated_states);

struct state_type;
typedef const struct state_type* state_cref;

MACRO_STRUCTURE_DEFINITION(state_step) {
    char_hld transform_profile;
    transmitter_hld download;
    transmitter_hld upload;
    state_cref next_state;
};

MACRO_STRUCTURE_DEFINITION(state) {
    MACRO_VECTOR_DEFINITION(steps, state_step_type);

    transmitter_hld download;
    char_hld mind_profile;
};

void state_destruct(state_mv state_ptr);
state_hld state_copy(state_cref state);