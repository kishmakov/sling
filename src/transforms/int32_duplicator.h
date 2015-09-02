#pragma once

#include "transform.h"

void int32_duplicator_register(transform_description_ptr* head);

transform_ptr int32_duplicator_create();

context_ptr int32_duplicator_func(transform_ptr transform, context_ptr input);