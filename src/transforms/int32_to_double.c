#include "transforms/int32_to_double.h"

#include "types/double.h"
#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_hld int32_to_double_description = NULL;

const char* int32_to_double_input_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"int32\": 1}", "");

    return scheme;
}

const char* int32_to_double_output_scheme(transform_cref transform)
{
    (void) transform;
    static char* scheme = NULL;

    if (!scheme)
        scheme = context_scheme("{\"double\": 1}", "");

    return scheme;
}

const char* int32_to_double_profile(transform_cref transform)
{
    (void) transform;
    static const char* profile = "int32_to_double";
    return profile;
}

transform_hld int32_to_double_construct(void* seed)
{
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = seed;
    result->description = int32_to_double_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_to_double_profile(result), (size_t) result);

    return result;
}

static transform_hld int32_to_double_copy(transform_cref transform)
{
    assert(transform != NULL);
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = transform->bytes;
    result->description = int32_to_double_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s copied @ %zu.", int32_to_double_profile(transform), (size_t) result);

    return result;
}

static void int32_to_double_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_to_double_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_to_double_profile(*transform), (size_t) *transform);

    free(*transform);
    *transform = NULL;
}

static context_hld int32_to_double_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);

    assert((*input)->data_size == 1);
    assert((*input)->transforms_size == 0);
    assert(transform->description == int32_to_double_description);

    DEBUG(size_t source = (size_t) (*input)->data[0]);

    int32_t val = int32_datum_extract((*input)->data[0]);
    datum_destruct(&((*input)->data[0]));
    context_destruct(input);

    context_hld result = context_construct(1, 0);
    result->data[0] = double_datum_construct((double) val);

    DLOG("%zu converted to %zu.", source, (size_t) result->data[0]);

    return result;
}

void int32_to_double_register(transform_description_io head)
{
    MACRO_TRANSFORM_INITIALIZER(int32_to_double);

    int32_to_double_description->next = *head;
    *head = int32_to_double_description;
}
