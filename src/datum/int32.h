#pragma once

#include "datum/datum.h"

void register_int32_datum();

datum_ptr create_int32_datum(int32_t value);
