#include "minds/int32_sign.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static mind_description_ptr int32_sign_description = NULL;

static char* int32_sign_input = NULL;
static char* int32_sign_decision = NULL;
static const char* int32_sign_profile = "int32_sign";
static const char* alternatives[] = {"-", "0", "+"};
static const uint32_t alternatives_number = sizeof(alternatives) / sizeof(const char*);

mind_ptr int32_sign_construct()
{
    mind_ptr result = malloc(sizeof(mind_type));
    result->bytes = NULL;
    result->description = int32_sign_description;

    DEBUG(allocation_list_insert(&allocated_minds, result));
    DLOG("%s constructed @ %zu.", int32_sign_profile, (size_t) result);

    return result;
}

static void int32_sign_destruct(mind_ptr* mind_holder)
{
    assert(mind_holder != NULL);
    assert(*mind_holder != NULL);
    assert((*mind_holder)->description == int32_sign_description);

    DEBUG(allocation_list_remove(&allocated_minds, *mind_holder));
    DLOG("%s destructed @ %zu.", int32_sign_profile, (size_t) *mind_holder);

    free(*mind_holder);
    *mind_holder = NULL;
}

static uint32_t int32_sign_function(mind_cptr mind, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    assert(*input_holder != NULL);
    context_ptr input = *input_holder;

    assert(input->data_size == 1);
    assert(input->transforms_size == 0);
    assert(mind->description == int32_sign_description);

    int32_t v = int32_datum_extract(input->data[0]);
    datum_destruct(&(input->data[0]));
    context_destruct(input_holder);

    return v < 0 ? 0 : (v > 0 ? 2 : 1);
}

void int32_sign_register(mind_description_ptr* head)
{
    int32_sign_input = context_scheme("{\"int32\": 1}", "");
    int32_sign_decision = decision_scheme(alternatives, alternatives_number);

    MACRO_MIND_INITIALIZER(int32_sign);

    int32_sign_description->next = *head;
    *head = int32_sign_description;
}
