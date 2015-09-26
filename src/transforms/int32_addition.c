#include "transforms/int32_addition.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_addition_description = NULL;

static char* int32_addition_input = NULL;
static char* int32_addition_output = NULL;
static const char* int32_addition_profile = "int32_add";

transform_ptr int32_addition_construct()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_addition_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_addition_profile, (size_t) result);

    return result;
}

static void int32_addition_destruct(transform_holder transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_addition_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_addition_profile, (size_t) *transform);

    free(*transform);
    *transform = NULL;
}

static context_ptr int32_addition_function(transform_cptr transform, context_holder input)
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

    context_ptr result = context_construct(1, 0);
    result->data[0] = int32_datum_construct(v0 + v1);
    return result;
}

transform_description_ptr int32_addition_register(transform_description_cptr head)
{
    int32_addition_input = context_scheme("{\"int32\": 1}, {\"int32\": 1}", "");
    int32_addition_output = context_scheme("{\"int32\": 1}", "");

    MACRO_TRANSFORM_INITIALIZER(int32_addition);

    int32_addition_description->next = head;
    return int32_addition_description;
}
