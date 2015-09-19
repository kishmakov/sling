#include "types/datum.h"

#include "utils/log.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list allocated_data = NULL);

datum_ptr datum_construct(type_description_cptr description, const void* src)
{
    assert(description != NULL); // description registred?
    assert(description->size > 0); // data types must contain something

    datum_ptr result = malloc(sizeof(datum_type));
    result->description = description;
    result->bytes = malloc(description->size);
    if (src != NULL)
        memcpy(result->bytes, src, description->size);

    DEBUG(allocation_list_insert(&allocated_data, result));
    LOG("%s constructed @ %zu.", description->scheme, (size_t) result);

    return result;
}

void datum_destruct(datum_ptr* datum_holder)
{
    assert(datum_holder != NULL);
    assert(*datum_holder != NULL);

    type_description_cptr description = (*datum_holder)->description;

    assert(description != NULL);

    DEBUG(allocation_list_remove(&allocated_data, *datum_holder));
    LOG("%s destructed @ %zu.", description->scheme, (size_t) *datum_holder);

    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};

datum_ptr datum_copy(datum_cptr datum)
{
    return datum_construct(datum->description, datum->bytes);
}

void datum_extract_value(datum_cptr datum, void* dst)
{
    memcpy(dst, datum->bytes, datum->description->size);
}
