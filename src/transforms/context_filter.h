#pragma once

#include "transforms/transform.h"

void context_filter_register(transform_description_io head);

transform_hld build_context_filter(
    uint32_t data_size,       uint32_t data[][2],
    uint32_t transforms_size, uint32_t transforms[][2]);

#define MACRO_BUILD_CONTEXT_FILTER(data, transforms) \
build_context_filter(sizeof(data) / 8, data, sizeof(transforms) / 8, transforms)
