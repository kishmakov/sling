#pragma once

#include "types/datum.h"

type_description_ptr double_type_register(type_description_ptr head);

datum_ptr double_datum_construct(double value);

double double_datum_extract(datum_cptr datum);
