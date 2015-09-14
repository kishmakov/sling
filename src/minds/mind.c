#include "minds/mind.h"

#include "utils/log.h"

#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_minds = NULL);

mind_ptr mind_create(mind_description_cptr description, const void* src)
{
    assert(description != NULL); // description registred?

    mind_ptr result = malloc(sizeof(mind_type));
    result->description = description;
    result->bytes = description->size > 0 ? malloc(description->size) : NULL;
    if (src != NULL)
        memcpy(result->bytes, src, description->size);

    DEBUG(allocation_list_insert(&allocated_minds, result));
    LOG("mind created @ %zu.", (size_t) result);

    return result;
}

void mind_delete(mind_ptr* mind_holder)
{
    DEBUG(allocation_list_remove(&allocated_minds, *mind_holder));
    LOG("mind deleted @ %zu.", (size_t) *mind_holder);

    free((*mind_holder)->bytes);
    free(*mind_holder);
    *mind_holder = NULL;
};

mind_ptr mind_copy(mind_cptr mind)
{
    return mind_create(mind->description, mind->bytes);
}