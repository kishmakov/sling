#include "transforms/context_filter.h"

#include "transforms/transform.h"
#include "types/double.h"
#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static transform_description_hld context_filter_description = NULL;

static const char* context_filter_input_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("FixMe", "FixMe");

    return scheme;
}

static const char* context_filter_output_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("FixMe", "FixMe");

    return scheme;
}

static const char* context_filter_profile(transform_cref transform)
{
    assert(transform != NULL);
    assert(transform->description == context_filter_description);

    static const size_t MAX_MESSAGE_SIZE = 500;
    static char profile[MAX_MESSAGE_SIZE];
    sprintf(profile, "%s", "context_filter");

    int32_t val;
    memcpy((void*) &val, transform->internal_data, 4);

    memset(profile, 0, sizeof(profile));
    return profile;
}

static transform_hld context_filter_construct(void_mv transmitter)
{
    transform_hld result = malloc(sizeof(transform_type));
    result->internal_data = *transmitter;
    *transmitter = NULL;
    result->description = context_filter_description;
    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", context_filter_profile(result), (size_t) result);

    return result;
}

static transform_hld context_filter_copy(transform_cref transform)
{
    assert(transform != NULL);
    assert(transform->description == context_filter_description);

    transform_hld result = malloc(sizeof(transform_type));
    result->internal_data = transmitter_copy((transmitter_cref) transform->internal_data);
    result->description = context_filter_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s copied @ %zu.", context_filter_profile(transform), (size_t) result);

    return result;
}

static void context_filter_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == context_filter_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", context_filter_profile(*transform), (size_t) *transform);

    transmitter_destruct((transmitter_mv) ((*transform)->internal_data));
    free(*transform);
    *transform = NULL;
}

static context_hld context_filter_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);

    assert((*input)->data_size == 1);
    assert((*input)->transforms_size == 0);
    assert(transform->description == context_filter_description);

    transmitter_cref transmitter = (transmitter_cref) transform->internal_data;
    context_hld output = context_construct(0, 0);
    transmit_move(transmitter, output, *input);

    for (uint32_t id = 0; id < (*input)->data_size; id++)
        if ((*input)->data[id] != 0)
            datum_destruct(&((*input)->data[id]));

    for (uint32_t id = 0; id < (*input)->transforms_size; id++)
        if ((*input)->transforms[id] != 0)
            transform_destruct(&((*input)->transforms[id]));

    DLOG("%s filtered %zu -> %zu.", context_filter_profile(transform), (size_t) *input, (size_t) output);
    context_destruct(input);
    return output;
}

void context_filter_register(transform_description_io head)
{
    MACRO_TRANSFORM_INITIALIZER(context_filter);

    context_filter_description->next = *head;
    *head = context_filter_description;
}

transform_hld build_context_filter(transmitter_mv transmitter)
{
    return context_filter_construct((void_mv) transmitter);
}
