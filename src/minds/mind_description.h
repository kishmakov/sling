#pragma once

#include "context.h"
#include "utils/utils.h"

#include <stdint.h>

void init_minds_descriptions();

struct mind_type;
typedef struct mind_type* mind_ptr;
typedef mind_ptr* mind_mv;
typedef const struct mind_type* mind_cref;

MACRO_STRUCTURE_DEFINITION(mind_description)
{
    mind_description_cref next;

    const char * input_scheme;
    const char * decision_scheme;
    const char * profile;

    // transform methods

    mind_ptr (*construct)(void);
    void (*destruct)(mind_mv mind);
    uint32_t (*function)(mind_cref mind, context_mv input);
};

mind_description_cref minds_descriptions();

