#include "minds/mind.h"

#include "utils/log.h"

#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_minds = NULL);

mind_ptr mind_construct(mind_description_cref description)
{
    assert(description != NULL); // description registred?
    assert(description->construct != NULL);
    return description->construct();

    // mind_ptr result = malloc(sizeof(mind_type));
    // result->description = description;
    // result->bytes = description->size > 0 ? malloc(description->size) : NULL;
    // if (src != NULL)
    //     memcpy(result->bytes, src, description->size);

    // DEBUG(allocation_list_insert(&allocated_minds, result));
    // LOG("mind constructd @ %zu.", (size_t) result);

    // return result;
}

void mind_destruct(mind_mv mind)
{
    assert(mind != NULL);
    assert(*mind != NULL);

    mind_description_cref description = (*mind)->description;

    assert(description != NULL);
    assert(description->destruct != NULL);
    description->destruct(mind);
    assert(*mind == NULL);


    // DEBUG(allocation_list_remove(&allocated_minds, *mind));
    // LOG("mind destructd @ %zu.", (size_t) *mind);

    // free((*mind)->bytes);
    // free(*mind);
    // *mind = NULL;
};

// mind_ptr mind_copy(mind_cref mind)
// {
//     return mind_construct(mind->description, mind->bytes);
// }

uint32_t mind_function(mind_cref mind, context_mv input)
{
    assert(input != NULL);
    assert(*input != NULL);
    assert(mind->description != NULL);
    assert(mind->description->function != NULL);
    uint32_t result = mind->description->function(mind, input);
    assert(*input == NULL);
    return result;
}
