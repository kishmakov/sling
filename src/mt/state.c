#include "mt/state.h"

#include <assert.h>
#include <stdlib.h>

state_hld state_copy(state_cref state)
{
    (void) state; // FixMe
    state_hld result = malloc(sizeof(state_type));
    return result;
}