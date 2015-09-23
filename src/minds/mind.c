#include "minds/mind.h"

#include "utils/log.h"

#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_minds = NULL);

mind_ptr mind_construct(mind_description_cptr description)
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

void mind_destruct(mind_ptr* mind_holder)
{
    assert(mind_holder != NULL);
    assert(*mind_holder != NULL);

    mind_description_cptr description = (*mind_holder)->description;

    assert(description != NULL);
    assert(description->destruct != NULL);
    description->destruct(mind_holder);
    assert(*mind_holder == NULL);


    // DEBUG(allocation_list_remove(&allocated_minds, *mind_holder));
    // LOG("mind destructd @ %zu.", (size_t) *mind_holder);

    // free((*mind_holder)->bytes);
    // free(*mind_holder);
    // *mind_holder = NULL;
};

// mind_ptr mind_copy(mind_cptr mind)
// {
//     return mind_construct(mind->description, mind->bytes);
// }

uint32_t mind_function(mind_cptr mind, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    assert(*input_holder != NULL);
    assert(mind->description != NULL);
    assert(mind->description->function != NULL);
    uint32_t result = mind->description->function(mind, input_holder);
    assert(*input_holder == NULL);
    return result;
}
