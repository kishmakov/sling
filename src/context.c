#include "context.h"

#include "datum.h"
#include "transform.h"

#include <stdlib.h>

context_ptr context_create(uint32_t data_size, uint32_t transforms_size) {
    context_ptr result = malloc(sizeof(context_type));
    result->data_size = data_size;
    result->data = data_size ? malloc(data_size * sizeof(datum_type)) : NULL;
    result->transforms_size = transforms_size;
    result->transforms = transforms_size ? malloc(transforms_size * sizeof(transform_type)) : NULL;

    return result;
}