#include "minds/int32_compare.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static mind_description_ptr int32_compare_description = NULL;

static char* int32_compare_input = NULL;
static char* int32_compare_decision = NULL;
static const char* int32_compare_profile = "int32_compare";
static const char* alternatives[] = {"1 < 2", "1 == 2", "1 > 2"};
static const uint32_t alternatives_number = sizeof(alternatives) / sizeof(const char*);

mind_ptr int32_compare_construct()
{
    mind_ptr result = malloc(sizeof(mind_type));
    result->bytes = NULL;
    result->description = int32_compare_description;

    DEBUG(allocation_list_insert(&allocated_minds, result));
    DLOG("%s constructed @ %zu.", int32_compare_profile, (size_t) result);

    return result;
}

static void int32_compare_destruct(mind_holder mind)
{
    assert(mind != NULL);
    assert(*mind != NULL);
    assert((*mind)->description == int32_compare_description);

    DEBUG(allocation_list_remove(&allocated_minds, *mind));
    DLOG("%s destructed @ %zu.", int32_compare_profile, (size_t) *mind);

    free(*mind);
    *mind = NULL;
}

static uint32_t int32_compare_function(mind_cptr mind, context_holder input)
{
    assert(input != NULL);
    assert(*input != NULL);

    assert((*input)->data_size == 2);
    assert((*input)->transforms_size == 0);
    assert(mind->description == int32_compare_description);

    int32_t v0 = int32_datum_extract((*input)->data[0]);
    int32_t v1 = int32_datum_extract((*input)->data[1]);
    datum_destruct(&((*input)->data[0]));
    datum_destruct(&((*input)->data[1]));
    context_destruct(input);

    return v0 < v1 ? 0 : (v0 > v1 ? 2 : 1);
}

mind_description_ptr int32_compare_register(mind_description_cptr head)
{
    int32_compare_input = context_scheme("{\"int32\": 1}, {\"int32\": 1}", "");
    int32_compare_decision = decision_scheme(alternatives, alternatives_number);

    MACRO_MIND_INITIALIZER(int32_compare);

    int32_compare_description->next = head;
    return int32_compare_description;
}
