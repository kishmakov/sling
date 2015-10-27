#pragma once

#include "types/type_description.h"
#include "utils/diagnostics.h"
#include "utils/utils.h"

DEBUG(extern allocation_list_hld allocated_data);

MACRO_STRUCTURE_DEFINITION(datum)
{
    void_hld bytes;
    type_description_cref description;
};

datum_hld datum_construct(type_description_cref description, void_mv src);
void      datum_destruct(datum_mv datum);
datum_hld datum_copy(datum_cref datum);

void_hld datum_extract_value(datum_cref datum);

