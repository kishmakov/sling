#include "context.h"

#include "transforms/transform.h"
#include "types/datum.h"
#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_contexts = NULL);

context_ptr context_construct(uint32_t data_size, uint32_t transforms_size)
{
    context_ptr result = malloc(sizeof(context_type));
    MACRO_VECTOR_ALLOCATE(result->data, datum_ptr, data_size);
    MACRO_VECTOR_ALLOCATE(result->transforms, transform_ptr, transforms_size);

    DEBUG(allocation_list_insert(&allocated_contexts, result));
    DLOG("context constructed @ %zu.", (size_t) result);

    return result;
}

void context_destruct(context_holder context)
{
    assert(context != NULL);
    assert(*context != NULL);

    DEBUG(allocation_list_remove(&allocated_contexts, *context));
    DLOG("context destructed @ %zu.", (size_t) *context);

#if DEBUG_MODE
    for (int id = 0; id < (*context)->data_size; id++)
        assert((*context)->data[id] == NULL);

    for (int id = 0; id < (*context)->transforms_size; id++)
        assert((*context)->transforms[id] == NULL);
#endif

    free((*context)->data);
    free((*context)->transforms);
    free(*context);
    *context = NULL;
}