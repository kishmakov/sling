#pragma once

#include "type_description.h"
#include "utils.h"

MACRO_STRUCTURE_DEFINITION(datum) {
    void* bytes;
    type_description_ptr description;
};

datum_ptr datum_create(type_description_ptr description, const void* src);

void datum_extract_value(const datum_type* datum, void* dst);

void datum_remove(datum_ptr* datum_holder);
