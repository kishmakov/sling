#include "types/datum.h"

#include "utils/log.h"

#include <memory.h>
#include <stdlib.h>

DEBUG(allocation_list_node_ptr allocated_datums = NULL);

datum_ptr datum_create(type_description_cptr description, const void* src)
{
    assert(description != NULL); // description registred?
    assert(description->size > 0); // data types must contain something

    datum_ptr result = malloc(sizeof(datum_type));
    result->description = description;
    result->bytes = malloc(description->size);
    if (src != NULL)
        memcpy(result->bytes, src, description->size);

    DEBUG(allocation_list_insert(&allocated_datums, result));
    LOG("datum created @ %zu.", (size_t) result);

    return result;
}

void datum_delete(datum_ptr* datum_holder)
{
    DEBUG(allocation_list_remove(&allocated_datums, *datum_holder));
    LOG("datum deleted @ %zu.", (size_t) *datum_holder);

    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};

datum_ptr datum_copy(datum_cptr datum)
{
    return datum_create(datum->description, datum->bytes);
}

void datum_extract_value(datum_cptr datum, void* dst)
{
    memcpy(dst, datum->bytes, datum->description->size);
}
