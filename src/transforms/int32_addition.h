#pragma once

#include "transform.h"

void int32_addition_register(transform_description_ptr* head);

transform_ptr int32_addition_construct();

context_ptr int32_addition_func(transform_ptr transform, context_ptr* input_holder);