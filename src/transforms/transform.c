#include "transforms/transform.h"

#include <assert.h>
#include <stdlib.h>

DEBUG(allocation_list_hld allocated_transforms = NULL);

transform_hld transform_construct(transform_description_cref description, void_mv data)
{
    assert(description != NULL); // description registred?
    assert(description->construct != NULL);
    return description->construct(data);
}

transform_hld transform_copy(transform_cref transform)
{
    assert(transform != NULL);
    assert(transform->description != NULL);
    assert(transform->description->copy != NULL);

    return transform->description->copy(transform);
}

void transform_destruct(transform_mv transform)
{
    assert(transform != NULL);
    assert(*transform != NULL);

    transform_description_cref description = (*transform)->description;

    assert(description != NULL);
    assert(description->destruct != NULL);
    description->destruct(transform);
    assert(*transform == NULL);
}

context_hld transform_function(transform_cref transform, context_mv input)
{
    assert(input != NULL);
    assert(*input != NULL);
    assert(transform->description != NULL);
    assert(transform->description->function != NULL);
    context_hld result = transform->description->function(transform, input);
    assert(*input == NULL);
    return result;
}
