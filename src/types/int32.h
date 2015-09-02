#pragma once

#include "datum.h"

void register_int32_type(type_description_ptr* head);

datum_ptr create_int32_datum(int32_t value);
