#include "transforms/int32_duplicator.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_duplicator_description = NULL;

static char* int32_duplicator_input = NULL;
static char* int32_duplicator_output = NULL;
static const char* int32_duplicator_profile = "int32_dupl";

transform_ptr int32_duplicator_construct()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_duplicator_description;

    DEBUG(allocation_list_insert(&allocated_transforms, result));
    DLOG("%s constructed @ %zu.", int32_duplicator_profile, (size_t) result);

    return result;
}

static void int32_duplicator_destruct(transform_ptr* transform_holder)
{
    assert(transform_holder != NULL);
    assert(*transform_holder != NULL);
    assert((*transform_holder)->description == int32_duplicator_description);

    DEBUG(allocation_list_remove(&allocated_transforms, *transform_holder));
    DLOG("%s destructed @ %zu.", int32_duplicator_profile, (size_t) *transform_holder);

    free(*transform_holder);
    *transform_holder = NULL;
}

static context_ptr int32_duplicator_function(transform_cptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    assert(*input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 1);
    assert(input->transforms_size == 0);
    assert(transform->description == int32_duplicator_description);

    datum_ptr datum = input->data[0];
    input->data[0] = NULL;
    context_destruct(input_holder);

    context_ptr result = context_construct(2, 0);
    result->data[0] = datum;
    result->data[1] = datum_copy(datum);

    DLOG("forked %zu from %zu.", (size_t) result->data[1], (size_t) datum);

    return result;
}

void int32_duplicator_register(transform_description_ptr* head)
{
    int32_duplicator_input = context_scheme("{\"int32\": 1}", "");
    int32_duplicator_output = context_scheme("{\"int32\": 1}, {\"int32\": 1}", "");

    MACRO_TRANSFORM_INITIALIZER(int32_duplicator);

    int32_duplicator_description->next = *head;
    *head = int32_duplicator_description;
}

