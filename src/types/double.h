#pragma once

#include "datum.h"

void register_double_type(type_description_ptr* head);

datum_ptr create_double_datum(double value);
