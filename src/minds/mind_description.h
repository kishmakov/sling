#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

void init_minds_descriptions();

struct mind_type;
typedef struct mind_type* mind_ptr;
typedef const struct mind_type* mind_cptr;

MACRO_STRUCTURE_DEFINITION(mind_description)
{
    mind_description_cptr next;

    const char * input_scheme;
    const char * decision_scheme;
    const char * profile;

    // transform methods

    mind_ptr (*construct)(void);
    void (*destruct)(mind_ptr* mind_holder);
    uint32_t (*function)(mind_cptr mind, context_ptr* input_holder);
};

mind_description_ptr minds_descriptions();

