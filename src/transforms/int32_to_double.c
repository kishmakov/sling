#include "transforms/int32_to_double.h"

#include "types/double.h"
#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_to_double_description = NULL;

static char* int32_to_double_input = NULL;
static char* int32_to_double_output = NULL;
static const char* int32_to_double_profile = "int32_to_double";

transform_ptr int32_to_double_construct()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_to_double_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_to_double_profile, (size_t) result);

    return result;
}

static void int32_to_double_destruct(transform_ptr* transform_holder)
{
    assert(transform_holder != NULL);
    assert(*transform_holder != NULL);
    assert((*transform_holder)->description == int32_to_double_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform_holder));
    DLOG("%s destructed @ %zu.", int32_to_double_profile, (size_t) *transform_holder);

    free(*transform_holder);
    *transform_holder = NULL;
}

static context_ptr int32_to_double_function(transform_cptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 1);
    assert(input->transforms_size == 0);
    assert(transform->description == int32_to_double_description);

    DEBUG(size_t source = (size_t) input->data[0]);

    int32_t val = int32_datum_extract(input->data[0]);
    datum_destruct(&(input->data[0]));
    context_destruct(input_holder);

    context_ptr result = context_construct(1, 0);
    result->data[0] = double_datum_construct((double) val);

    DLOG("%zu converted to %zu.", source, (size_t) result->data[0]);

    return result;
}

void int32_to_double_register(transform_description_ptr* head)
{
    int32_to_double_input = scheme_description("{\"int32\": 1}", "");
    int32_to_double_output = scheme_description("{\"double\": 1}", "");

    MACRO_TRANSFORM_INITIALIZER(int32_to_double);

    int32_to_double_description->next = *head;
    *head = int32_to_double_description;
}
