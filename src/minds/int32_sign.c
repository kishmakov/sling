#include "minds/int32_sign.h"

#include "types/int32.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

static mind_description_hld int32_sign_description = NULL;

static char* int32_sign_input = NULL;
static char* int32_sign_decision = NULL;
static const char* int32_sign_profile = "int32_sign";
static const char* alternatives[] = {"-", "0", "+"};
static const uint32_t alternatives_number = sizeof(alternatives) / sizeof(const char*);

mind_hld int32_sign_construct()
{
    mind_hld result = malloc(sizeof(mind_type));
    result->bytes = NULL;
    result->description = int32_sign_description;

    DEBUG(allocation_list_insert(&allocated_minds, result));
    DLOG("%s constructed @ %zu.", int32_sign_profile, (size_t) result);

    return result;
}

static void int32_sign_destruct(mind_mv mind)
{
    assert(mind != NULL);
    assert(*mind != NULL);
    assert((*mind)->description == int32_sign_description);

    DEBUG(allocation_list_remove(&allocated_minds, *mind));
    DLOG("%s destructed @ %zu.", int32_sign_profile, (size_t) *mind);

    free(*mind);
    *mind = NULL;
}

static uint32_t int32_sign_function(mind_cref mind, context_mv input)
{
    assert(input != NULL);
    assert(*input != NULL);

    assert((*input)->data_size == 1);
    assert((*input)->transforms_size == 0);
    assert(mind->description == int32_sign_description);

    int32_t v = int32_datum_extract((*input)->data[0]);
    datum_destruct(&((*input)->data[0]));
    context_destruct(input);

    return v < 0 ? 0 : (v > 0 ? 2 : 1);
}

mind_description_hld int32_sign_register(mind_description_cref head)
{
    int32_sign_input = context_scheme("{\"int32\": 1}", "");
    int32_sign_decision = decision_scheme(alternatives, alternatives_number);

    MACRO_MIND_INITIALIZER(int32_sign);

    int32_sign_description->next = head;
    return int32_sign_description;
}
