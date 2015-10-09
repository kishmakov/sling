#pragma once

#include "transforms/transform.h"
#include "transmitter.h"

void context_filter_register(transform_description_io head);

transform_hld build_context_filter(transmitter_mv transmitter);
