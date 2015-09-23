#include "transforms/transform.h"

#include <assert.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_transforms = NULL);

transform_ptr transform_construct(transform_description_cptr description)
{
    assert(description != NULL); // description registred?
    assert(description->construct != NULL);
    return description->construct();
}

void transform_destruct(transform_ptr* transform_holder)
{
    assert(transform_holder != NULL);
    assert(*transform_holder != NULL);

    transform_description_cptr description = (*transform_holder)->description;

    assert(description != NULL);
    assert(description->destruct != NULL);
    description->destruct(transform_holder);
    assert(*transform_holder == NULL);
}

context_ptr transform_function(transform_cptr transform, context_ptr* input_holder)
{
    assert(input_holder != NULL);
    assert(*input_holder != NULL);
    assert(transform->description != NULL);
    assert(transform->description->function != NULL);
    context_ptr result = transform->description->function(transform, input_holder);
    assert(*input_holder == NULL);
    return result;
}
