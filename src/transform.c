#include "transform.h"

#include <assert.h>
#include <stdlib.h>

transform_ptr transform_construct(transform_description_cptr description)
{
    assert(description->construct != NULL);
    return description->construct();
}

void transform_destruct(transform_ptr* transform_holder)
{
    assert(transform_holder != NULL);
    assert(*transform_holder != NULL);
    assert((*transform_holder)->description != NULL);
    assert((*transform_holder)->description->destruct != NULL);
    (*transform_holder)->description->destruct(transform_holder);
    assert(*transform_holder == NULL);
}

context_ptr transform_function(transform_cptr transform, context_ptr* input_holder)
{
    assert(transform->description != NULL);
    assert(transform->description->function != NULL);
    return transform->description->function(transform, input_holder);
}