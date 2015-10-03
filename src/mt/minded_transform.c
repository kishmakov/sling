#include "mt/minded_transform.h"

#include "context.h"
#include "minds/mind.h"
#include "transforms/transform.h"
#include "utils/log.h"
#include "utils/trie.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_hld minded_transform_description = NULL;

const char* minded_transform_input_scheme()
{
    static char* scheme = NULL;

    if (!scheme)
        scheme = "FixMe";

    return scheme;
}

const char* minded_transform_output_scheme()
{
    static char* scheme = NULL;

    if (!scheme)
        scheme = "FixMe";

    return scheme;
}

const char* minded_transform_profile()
{
    static const char* profile = "FixMe";
    return profile;
}

transform_hld minded_transform_construct(void* minded_transform_impl)
{
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = minded_transform_impl;
    result->description = minded_transform_description;

    return result;
}

static transform_hld minded_transform_copy(transform_cref transform)
{
    assert(transform->description == minded_transform_description);
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = transform->bytes; // FixMe
    result->description = minded_transform_description;

    return result;
}

static void minded_transform_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == minded_transform_description);

    free(*transform); // FixMe: remove impl
    *transform = NULL;
}

static context_hld minded_transform_function(transform_cref transform, context_mv context)
{
    assert(transform != NULL);
    assert(transform->bytes != NULL);

    assert(context != NULL);
    assert(*context != NULL);

    minded_transform_impl_cref mt = (minded_transform_impl_cref) transform->bytes;

    for (state_cref state = mt->start; state != mt->finish; ) {
        // mind decision
        context_hld mind_context = context_construct(0, 0);
        transmit_copy(state->download, mind_context, *context);
        mind_cref mind = trie_check(mt->minds, state->mind_profile);
        uint32_t next_id = mind_function(mind, &mind_context);
        context_destruct(&mind_context);
        // computation
        assert(next_id < state->steps_size);
        state_step_type* step = &(state->steps[next_id]);
        transform_cref transform = trie_check(mt->transforms, step->transform_profile);
        context_hld in_context = context_construct(0, 0);
        transmit_move(step->download, in_context, *context);
        context_hld out_context = transform_function(transform, &in_context);
        transmit_move(step->upload, *context, out_context);
        context_destruct(&in_context);
        context_destruct(&out_context);
        state = step->next_state;
    }

    context_hld result = *context;
    *context = NULL;

    return result;
}

transform_description_hld minded_transform_register(transform_description_cref head)
{
    MACRO_TRANSFORM_INITIALIZER(minded_transform);

    minded_transform_description->next = head;
    return minded_transform_description;
}