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

void transform_destruct(transform_holder transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);

    transform_description_cptr description = (*transform)->description;

    assert(description != NULL);
    assert(description->destruct != NULL);
    description->destruct(transform);
    assert(*transform == NULL);
}

context_ptr transform_function(transform_cptr transform, context_holder input)
{
    assert(input != NULL);
    assert(*input != NULL);
    assert(transform->description != NULL);
    assert(transform->description->function != NULL);
    context_ptr result = transform->description->function(transform, input);
    assert(*input == NULL);
    return result;
}
