#include "datum.h"

#include "utils/diagnostics.h"
#include "utils/log.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

datum_ptr datum_create(type_description_ptr description, const void* src)
{
    assert(description != NULL); // description registred?
    assert(description->size > 0); // data types must contain something
    datum_ptr result = malloc(sizeof(datum_type));
    result->description = description;
    result->bytes = malloc(description->size);
    if (src != NULL)
        memcpy(result->bytes, src, description->size);

    LOG_INFO("datum created @ %zu.", (size_t) result);
    return result;
}

void datum_extract_value(datum_cptr datum, void* dst)
{
    memcpy(dst, datum->bytes, datum->description->size);
}

void datum_remove(datum_ptr* datum_holder)
{
    LOG_INFO("datum removed @ %zu.", (size_t) *datum_holder);
    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};
