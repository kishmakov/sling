#pragma once

#include "transform.h"

transform_description_cptr get_int32_duplicator_description();

void int32_duplicator_register(transform_description_ptr* head);

// transform_ptr int32_duplicator_construct();

// context_ptr int32_duplicator_function(transform_ptr transform, context_ptr* input_holder);