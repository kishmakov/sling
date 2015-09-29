#pragma once

#include "types/datum.h"

type_description_hld double_type_register(type_description_cref head);

datum_hld double_datum_construct(double value);

double double_datum_extract(datum_cref datum);
