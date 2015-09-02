#include "datum.h"

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

    return result;
}

void datum_extract_value(const datum_type* datum, void* dst)
{
    memcpy(dst, datum->bytes, datum->description->size);
}

void datum_remove(datum_ptr* datum_holder) {
    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};
