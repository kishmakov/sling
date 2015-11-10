#include "mt/state.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void state_destruct(state_mv state_ptr)
{
    state_hld state = *state_ptr;

    free(state->steps); // FixMe: Proper steps destructors.
    if (state->download != NULL)
        transmitter_destruct(&(state->download));
    assert(state->download == NULL);
    free(state->mind_profile);

    free(state);
    *state_ptr = NULL;
}

state_hld state_copy(state_cref state)
{
    state_hld result = malloc(sizeof(state_type));
    MACRO_VECTOR_ALLOCATE(result->steps, state_step_type, state->steps_size);
    for (uint32_t id = 0; id < state->steps_size; id++) {
        MACRO_STRING_COPY(result->steps[id].transform_profile, state->steps[id].transform_profile);
        result->steps[id].download = transmitter_copy(state->steps[id].download);
        result->steps[id].upload = transmitter_copy(state->steps[id].upload);
    }
    result->download = transmitter_copy(state->download);
    MACRO_STRING_COPY(result->mind_profile, state->mind_profile);

    return result;
}
