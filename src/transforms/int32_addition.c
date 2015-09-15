#include "transforms/int32_addition.h"

#include "types/int32.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_addition_description = NULL;

static char* int32_addition_input = NULL;
static char* int32_addition_output = NULL;
static const char* int32_addition_profile = "int32_add";

void int32_addition_register(transform_description_ptr* head)
{
    int32_addition_input = scheme_description("{\"int32\": 1}, {\"int32\": 1}", "");
    int32_addition_output = scheme_description("{\"int32\": 1}", "");

    int32_addition_description = malloc(sizeof(transform_description_type));
    int32_addition_description->input_scheme = int32_addition_input;
    int32_addition_description->output_scheme = int32_addition_output;
    int32_addition_description->profile = int32_addition_profile;
    int32_addition_description->next = *head;

    *head = int32_addition_description;
}

transform_ptr int32_addition_construct()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_addition_description;

    return result;
}

context_ptr int32_addition_func(transform_ptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 2);
    assert(input->transforms_size == 0);
    assert(transform->description == int32_addition_description);

    int32_t v0 = int32_datum_extract(input->data[0]);
    int32_t v1 = int32_datum_extract(input->data[1]);
    datum_delete(&(input->data[0]));
    datum_delete(&(input->data[1]));
    context_delete(input_holder);

    context_ptr result = context_construct(1, 0);
    result->data[0] = int32_datum_construct(v0 + v1);

    return result;
}
