#pragma once

#include "datum/datum.h"

void register_double_datum(datum_description_ptr* head);

datum_ptr create_double_datum(double value);
