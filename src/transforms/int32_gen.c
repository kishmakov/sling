#include "transforms/int32_gen.h"

#include "types/double.h"
#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static transform_description_hld int32_gen_description = NULL;

static const char* int32_gen_input_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("", "");

    return scheme;
}

static const char* int32_gen_output_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}", "");

    return scheme;
}

static const char* int32_gen_profile(transform_cref transform)
{
    assert(transform != NULL);
    assert(transform->description == int32_gen_description);
    int32_t val;
    memcpy((void*) &val, transform->internal_data, 4);

    static char profile[20];
    memset(profile, 0, sizeof(profile));
    sprintf(profile, "%s%d", "int32_gen_", val);
    return profile;
}

static transform_hld int32_gen_construct(void_mv internal_data)
{
    transform_hld result = malloc(sizeof(transform_type));
    result->internal_data = *internal_data;
    *internal_data = NULL;
    result->description = int32_gen_description;
    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_gen_profile(result), (size_t) result);

    return result;
}

static transform_hld int32_gen_copy(transform_cref transform)
{
    assert(transform != NULL);
    assert(transform->description == int32_gen_description);

    transform_hld result = malloc(sizeof(transform_type));
    memcpy(result->internal_data, transform->internal_data, 4);
    result->description = int32_gen_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s copied @ %zu.", int32_gen_profile(transform), (size_t) result);

    return result;
}

static void int32_gen_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_gen_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_gen_profile(*transform), (size_t) *transform);

    free(*transform);
    *transform = NULL;
}

static context_hld int32_gen_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);

    assert((*input)->data_size == 0);
    assert((*input)->transforms_size == 0);
    assert(transform->description == int32_gen_description);
    context_destruct(input);

    int32_t val;
    memcpy((void*) &val, transform->internal_data, 4);

    context_hld result = context_construct(1, 0);
    result->data[0] = int32_datum_construct(val);

    DLOG("%zu generated out of %d.", (size_t) result, val);

    return result;
}

void int32_gen_register(transform_description_io head)
{
    MACRO_TRANSFORM_INITIALIZER(int32_gen);

    int32_gen_description->next = *head;
    *head = int32_gen_description;
}

transform_hld build_int32_gen(int32_t val)
{
    void_hld internal_data = malloc(4);
    memcpy(internal_data, &val, 4);
    return int32_gen_construct(&internal_data);
}

