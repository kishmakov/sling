#pragma once

#include "transform.h"

void int32_to_double_register(transform_description_ptr* head);

transform_ptr int32_to_double_construct();

context_ptr int32_to_double_function(transform_ptr transform, context_ptr* input_holder);