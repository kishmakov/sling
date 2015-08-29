#pragma once

#include "datum/description.h"

typedef struct {
    void* bytes;
    datum_description_ptr description;
} datum_type;

typedef datum_type* datum_ptr;

void remove_datum(datum_ptr* datum_holder);
