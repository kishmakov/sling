#pragma once

#include "transform.h"

void register_int32_duplicator(transform_description_ptr* head);

context_ptr int32_duplicator_func(transform_ptr transform, context_ptr input);