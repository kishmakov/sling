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

mind_ptr mind_create(mind_description_cptr description, const void* src);

void mind_delete(mind_ptr* mind_holder);

mind_ptr mind_copy(mind_cptr mind);

void mind_extract_value(mind_cptr mind, void* dst);

