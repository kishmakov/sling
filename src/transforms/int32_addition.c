#include "transforms/int32_addition.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_hld int32_addition_description = NULL;

const char* int32_addition_input_scheme()
{
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}, {\"int32\": 1}", "");

    return scheme;
}

const char* int32_addition_output_scheme()
{
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}", "");

    return scheme;
}

const char* int32_addition_profile()
{
    static const char* profile = "int32_add";
    return profile;
}

transform_hld int32_addition_construct()
{
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_addition_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_addition_profile(), (size_t) result);

    return result;
}

static transform_hld int32_addition_copy(transform_cref transform)
{
    (void) transform;

    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_addition_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s copied @ %zu.", int32_addition_profile(), (size_t) result);

    return result;
}

static void int32_addition_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_addition_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_addition_profile(), (size_t) *transform);

    free(*transform);
    *transform = NULL;
}

static context_hld int32_addition_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);
    assert(*input != NULL);

    assert((*input)->data_size == 2);
    assert((*input)->transforms_size == 0);
    assert(transform->description == int32_addition_description);

    int32_t v0 = int32_datum_extract((*input)->data[0]);
    int32_t v1 = int32_datum_extract((*input)->data[1]);
    datum_destruct(&((*input)->data[0]));
    datum_destruct(&((*input)->data[1]));
    context_destruct(input);

    context_hld result = context_construct(1, 0);
    result->data[0] = int32_datum_construct(v0 + v1);
    return result;
}

transform_description_hld int32_addition_register(transform_description_cref head)
{
    MACRO_TRANSFORM_INITIALIZER(int32_addition);

    int32_addition_description->next = head;
    return int32_addition_description;
}
