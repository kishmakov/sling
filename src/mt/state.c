#include "mt/state.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

state_hld state_copy(state_cref state)
{
    state_hld result = malloc(sizeof(state_type));
    MACRO_VECTOR_ALLOCATE(result->steps, state_step_type, state->steps_size);
    // for (uint32_t id = 0; id < state->steps_size; id++) FixMe;
    result->download = transmitter_copy(state->download);
    MACRO_STRING_COPY(result->mind_profile, state->mind_profile);

    return result;
}