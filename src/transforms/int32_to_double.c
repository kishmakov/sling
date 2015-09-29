#include "transforms/int32_to_double.h"

#include "types/double.h"
#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_hld int32_to_double_description = NULL;

static char* int32_to_double_input = NULL;
static char* int32_to_double_output = NULL;
static const char* int32_to_double_profile = "int32_to_double";

transform_hld int32_to_double_construct()
{
    transform_hld result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_to_double_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_to_double_profile, (size_t) result);

    return result;
}

static void int32_to_double_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);
    assert((*transform)->description == int32_to_double_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform));
    DLOG("%s destructed @ %zu.", int32_to_double_profile, (size_t) *transform);

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

transform_description_hld int32_to_double_register(transform_description_cref head)
{
    int32_to_double_input = context_scheme("{\"int32\": 1}", "");
    int32_to_double_output = context_scheme("{\"double\": 1}", "");

    MACRO_TRANSFORM_INITIALIZER(int32_to_double);

    int32_to_double_description->next = head;
    return int32_to_double_description;
}
