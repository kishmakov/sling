#pragma once

#include "types/datum.h"

void int32_type_register(type_description_ptr* head);

datum_ptr int32_datum_construct(int32_t value);

int32_t int32_datum_extract(datum_cptr datum);
