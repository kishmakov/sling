#include "mt/minded_transform.h"

#include "context.h"
#include "minds/mind.h"
#include "transforms/transform.h"
#include "utils/log.h"
#include "utils/trie.h"

#include <assert.h>
#include <stdlib.h>

// static transform_description_ptr int32_duplicator_description = NULL;

// static char* int32_duplicator_input = NULL;
// static char* int32_duplicator_output = NULL;
// static const char* int32_duplicator_profile = "int32_x2";

// static void int32_duplicator_destruct(transform_mv transform)
// {
//     assert(transform != NULL);
//     assert(*transform != NULL);
//     assert((*transform)->description == int32_duplicator_description);

//     DEBUG(allocation_list_remove(&allocated_transforms, *transform));
//     DLOG("%s destructed @ %zu.", int32_duplicator_profile, (size_t) *transform);

//     free(*transform);
//     *transform = NULL;
// }

static context_hld minded_transform_function(transform_cref transform, context_mv context)
{
    assert(transform != NULL);
    assert(transform->bytes != NULL);

    assert(context != NULL);
    assert(*context != NULL);

    minded_transform_impl_cref mt = (minded_transform_impl_cref) transform->bytes;
    context_hld mind_context = context_construct(0, 0);

    for (state_cref state = mt->start; state != mt->finish; ) {
        transmit_copy(state->download, mind_context, *context);
        mind_cref mind = (mind_cref) trie_check(mt->minds, state->mind_profile);
        uint32_t decision = mind_function(mind, &mind_context);
    }

    context_hld result = *context;
    *context = NULL;

    return result;
}
