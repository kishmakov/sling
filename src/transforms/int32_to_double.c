#include "transforms/int32_to_double.h"

#include "types/double.h"
#include "types/int32.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_to_double_description = NULL;

static char* int32_to_double_input = NULL;
static char* int32_to_double_output = NULL;
static const char* int32_to_double_profile = "int32_to_double";

void int32_to_double_register(transform_description_ptr* head)
{
    int32_to_double_input = scheme_description("{\"int32\": 1}", "");
    int32_to_double_output = scheme_description("{\"double\": 1}", "");

    int32_to_double_description = malloc(sizeof(transform_description_type));
    int32_to_double_description->input_scheme = int32_to_double_input;
    int32_to_double_description->output_scheme = int32_to_double_output;
    int32_to_double_description->profile = int32_to_double_profile;
    int32_to_double_description->next = *head;

    *head = int32_to_double_description;
}

transform_ptr int32_to_double_construct()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_to_double_description;

    return result;
}

context_ptr int32_to_double_func(transform_ptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 1);
    assert(input->transforms_size == 0);
    assert(transform->description == int32_to_double_description);

    int32_t val = int32_datum_extract(input->data[0]);
    datum_delete(&(input->data[0]));
    context_delete(input_holder);

    context_ptr result = context_construct(1, 0);
    result->data[0] = double_datum_construct((double) val);

    return result;
}