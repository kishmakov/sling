#pragma once

#include "datum.h"

void double_type_register(type_description_ptr* head);

datum_ptr double_datum_create(double value);
