#include "context.h"

#include "transforms/transform.h"
#include "types/datum.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

DEBUG(allocation_list_hld allocated_contexts = NULL);

context_hld context_construct(uint32_t data_size, uint32_t transforms_size)
{
    context_hld result = malloc(sizeof(context_type));
    MACRO_VECTOR_ALLOCATE(result->data, datum_hld, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms, transform_hld, transforms_size);

    DEBUG(allocation_list_insert(&allocated_contexts, result));
    DLOG("context constructed @ %zx.", (size_t) result);

    return result;
}

void context_destruct(context_mv context_ptr)
{
    assert(context_ptr != NULL);
    assert(*context_ptr != NULL);

    DEBUG(allocation_list_remove(&allocated_contexts, *context_ptr));
    DEBUG(size_t nonempty_data = 0);
    DEBUG(size_t nonempty_transforms = 0);

    for (int id = 0; id < (*context_ptr)->data_size; id++)
        if ((*context_ptr)->data[id] != NULL) {
            datum_destruct(&((*context_ptr)->data[id]));
            DEBUG(nonempty_data++);
        }

    for (int id = 0; id < (*context_ptr)->transforms_size; id++)
        if ((*context_ptr)->transforms[id] != NULL) {
            transform_destruct(&((*context_ptr)->transforms[id]));
            DEBUG(nonempty_transforms++);
        }

    DLOG("context destructed @ %zx with %zu data and %zu transforms.",
        (size_t) *context_ptr, nonempty_data, nonempty_transforms);

    free((*context_ptr)->data);
    free((*context_ptr)->transforms);
    free(*context_ptr);
    *context_ptr = NULL;
}

context_hld context_copy(context_cref context)
{
    assert(context != NULL);

    context_hld result = malloc(sizeof(context_type));
    MACRO_VECTOR_ALLOCATE(result->data, datum_hld, context->data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms, transform_hld, context->transforms_size);

    for (int id = 0; id < context->data_size; id++)
        result->data[id] = datum_copy(context->data[id]);

    for (int id = 0; id < context->transforms_size; id++)
        result->transforms[id] = transform_copy(context->transforms[id]);

    return result;
}