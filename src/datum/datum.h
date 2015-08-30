#pragma once

#include "datum/description.h"

typedef struct {
    void* bytes;
    datum_description_ptr description;
} datum_type;

typedef datum_type* datum_ptr;

datum_ptr create_datum(datum_description_ptr description, const void* src);

void remove_datum(datum_ptr* datum_holder);
