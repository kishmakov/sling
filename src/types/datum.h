#pragma once

#include "types/type_description.h"
#include "utils/diagnostics.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_node_ptr allocated_datums);

MACRO_STRUCTURE_DEFINITION(datum)
{
    void* bytes;
    type_description_cptr description;
};

datum_ptr datum_create(type_description_cptr description, const void* src);

void datum_delete(datum_ptr* datum_holder);

datum_ptr datum_copy(datum_cptr datum);

void datum_extract_value(datum_cptr datum, void* dst);
