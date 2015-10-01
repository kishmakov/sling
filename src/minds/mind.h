#pragma once

#include "minds/mind_description.h"
#include "utils/diagnostics.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_hld allocated_minds);

MACRO_STRUCTURE_DEFINITION(mind)
{
    void* bytes;
    mind_description_cref description;
};

mind_ptr mind_construct(mind_description_cref description);

void mind_destruct(mind_mv mind);

// mind_ptr mind_copy(mind_cref mind);

uint32_t mind_function(mind_cref mind, context_mv input);
