#include "transforms/int32_duplicator.h"

#include "types/int32.h"

#include <assert.h>
#include <stdlib.h>

static transform_description_ptr int32_duplicator_description = NULL;

static char* int32_duplicator_input = NULL;
static char* int32_duplicator_output = NULL;
static const char* int32_duplicator_profile = "int32_dupl";

void int32_duplicator_register(transform_description_ptr* head)
{
    int32_duplicator_input = scheme_description("{\"int32\": 1}", "");
    int32_duplicator_output = scheme_description("{\"int32\": 1}, {\"int32\": 1}", "");

    int32_duplicator_description = malloc(sizeof(transform_description_type));
    int32_duplicator_description->input_scheme = int32_duplicator_input;
    int32_duplicator_description->output_scheme = int32_duplicator_output;
    int32_duplicator_description->profile = int32_duplicator_profile;
    int32_duplicator_description->next = *head;

    *head = int32_duplicator_description;
}

transform_ptr int32_duplicator_create()
{
    transform_ptr result = malloc(sizeof(transform_type));
    result->bytes = NULL;
    result->description = int32_duplicator_description;

    return result;
}

context_ptr int32_duplicator_func(transform_ptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 1);
    assert(input->transforms_size == 0);
    assert(transform->description == int32_duplicator_description);

    context_ptr result = context_create(2, 0);

    result->data[0] = input->data[0];
    result->data[1] = datum_copy(input->data[0]);

    input->data[0] = NULL;
    context_delete(input_holder);

    return result;
}
