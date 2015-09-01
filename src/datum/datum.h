#pragma once

#include "datum/description.h"
#include "utils.h"

MACRO_STRUCTURE_DEFINITION(datum) {
    void* bytes;
    datum_description_ptr description;
};

datum_ptr create_datum(datum_description_ptr description, const void* src);

void remove_datum(datum_ptr* datum_holder);
