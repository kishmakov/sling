#include "transform.h"

#include <assert.h>
#include <stdlib.h>

transform_ptr transform_construct(transform_description_cptr description)
{
    assert(description->construct != NULL);
    return description->construct();
}

context_ptr transform_function(transform_cptr transform, context_ptr* input_holder)
{
    assert(transform->description != NULL);
    assert(transform->description->function != NULL);

    return transform->description->function(transform, input_holder);
}