#include "context.h"

#include "transform.h"
#include "types/datum.h"
#include "utils/log.h"

#include <stdlib.h>

DEBUG(allocation_list allocated_contexts = NULL);

context_ptr context_create(uint32_t data_size, uint32_t transforms_size)
{
    context_ptr result = malloc(sizeof(context_type));
    MACRO_VECTOR_ALLOCATE(result->data, datum_ptr, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms, transform_ptr, transforms_size);

    DEBUG(allocation_list_insert(&allocated_contexts, result));
    LOG("context created @ %zu.", (size_t) result);

    return result;
}

void context_delete(context_ptr* context_holder)
{
    DEBUG(allocation_list_remove(&allocated_contexts, *context_holder));
    LOG("context deleted @ %zu.", (size_t) *context_holder);

#if DEBUG_MODE
    context_ptr context = *context_holder;
    for (int id = 0; id < context->data_size; id++)
        assert(context->data[id] == NULL);

    for (int id = 0; id < context->transforms_size; id++)
        assert(context->transforms[id] == NULL);
#endif

    free((*context_holder)->data);
    free((*context_holder)->transforms);
    free(*context_holder);
    *context_holder = NULL;
}