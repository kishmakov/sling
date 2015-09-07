#include "context.h"

#include "datum.h"
#include "transform.h"

#include <stdlib.h>

context_ptr context_create(uint32_t data_size, uint32_t transforms_size)
{
    context_ptr result = malloc(sizeof(context_type));
    MACRO_VECTOR_ALLOCATE(result->data, datum_ptr, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms, transform_ptr, transforms_size);
    return result;
}

void context_delete(context_ptr* context_holder)
{
    free((*context_holder)->data);
    free((*context_holder)->transforms);
    free(*context_holder);
    *context_holder = NULL;
}