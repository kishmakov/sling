#include "types/datum.h"

#include "utils/log.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list_hld allocated_data = NULL);

datum_hld datum_construct(type_description_cref description, void_mv src)
{
    assert(description != NULL); // description registred?
    assert(description->size > 0); // data types must contain something

    datum_hld result = malloc(sizeof(datum_type));
    result->description = description;
    result->bytes = *src;
    *src = NULL;

    DEBUG(allocation_list_insert(&allocated_data, result));
    DLOG("%s constructed @ %zx.", description->scheme, (size_t) result);

    return result;
}

void datum_destruct(datum_mv datum)
{
    assert(datum != NULL);
    assert(*datum != NULL);

    type_description_cref description = (*datum)->description;

    assert(description != NULL);

    DEBUG(allocation_list_remove(&allocated_data, *datum));
    DLOG("%s destructed @ %zx.", description->scheme, (size_t) *datum);

    free((*datum)->bytes);
    free(*datum);
    *datum = NULL;
};

datum_hld datum_copy(datum_cref datum)
{
    void_hld bytes = malloc(datum->description->size);
    memcpy(bytes, datum->bytes, datum->description->size);
    return datum_construct(datum->description, &bytes);
}

void_hld datum_extract_value(datum_cref datum)
{
    void_hld bytes = malloc(datum->description->size);
    memcpy(bytes, datum->bytes, datum->description->size);
    return bytes;
}
