#pragma once

#include "datum/datum.h"

void register_int32_datum(datum_description_ptr* head);

datum_ptr create_int32_datum(int32_t value);
