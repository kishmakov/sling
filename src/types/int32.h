#pragma once

#include "types/datum.h"

type_description_hld int32_type_register(type_description_cref head);

datum_hld int32_datum_construct(int32_t value);

int32_t int32_datum_extract(datum_cref datum);
