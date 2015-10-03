#include "transforms/int32_duplicator.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_hld int32_duplicator_description = NULL;

const char* int32_duplicator_input_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}", "");

    return scheme;
}

const char* int32_duplicator_output_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}, {\"int32\": 1}", "");

    return scheme;
}

const char* int32_duplicator_profile(transform_cref transform)
{
    (void) transform;
    static const char* profile = "int32_dupl";
    return profile;
}

transform_hld int32_duplicator_construct(void* seed)
{
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = seed;
    result->description = int32_duplicator_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_duplicator_profile(result), (size_t) result);

    return result;
}

static transform_hld int32_duplicator_copy(transform_cref transform)
{
    (void) transform;

    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_duplicator_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s copied @ %zu.", int32_duplicator_profile(transform), (size_t) result);

    return result;
}

static void int32_duplicator_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_duplicator_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_duplicator_profile(*transform), (size_t) *transform);

    free(*transform);
    *transform = NULL;
}

static context_hld int32_duplicator_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);
    assert(*input != NULL);

    assert((*input)->data_size == 1);
    assert((*input)->transforms_size == 0);
    assert(transform->description == int32_duplicator_description);

    datum_hld datum = (*input)->data[0];
    (*input)->data[0] = NULL;
    context_destruct(input);

    context_hld result = context_construct(2, 0);
    result->data[0] = datum;
    result->data[1] = datum_copy(datum);

    DLOG("forked %zu from %zu.", (size_t) result->data[1], (size_t) datum);

    return result;
}

void int32_duplicator_register(transform_description_io head)
{
    MACRO_TRANSFORM_INITIALIZER(int32_duplicator);

    int32_duplicator_description->next = *head;
    *head = int32_duplicator_description;
}

