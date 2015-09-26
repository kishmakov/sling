#pragma once

#include "minds/mind_description.h"
#include "utils/diagnostics.h"
#include "utils/utils.h"

DEBUG(extern allocation_list allocated_minds);

MACRO_STRUCTURE_DEFINITION(mind)
{
    void* bytes;
    mind_description_cptr description;
};

mind_ptr mind_construct(mind_description_cptr description);

void mind_destruct(mind_holder mind);

// mind_ptr mind_copy(mind_cptr mind);

uint32_t mind_function(mind_cptr mind, context_holder input);
