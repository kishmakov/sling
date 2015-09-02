#include "datum.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

datum_ptr create_datum(type_description_ptr description, const void* src)
{
    assert(description != NULL); // description registred?
    datum_ptr result = malloc(sizeof(datum_type));
    result->description = description;
    result->bytes = malloc(description->size);
    if (src != NULL)
        memcpy(result->bytes, src, description->size);

    return result;
}

void remove_datum(datum_ptr* datum_holder) {
    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};
