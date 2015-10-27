#include "types/int32.h"

#include <assert.h>
#include <stdlib.h>

static type_description_hld int32_type_description = NULL;

static char* int32_type_scheme = "{\"int32\": 1}";

type_description_hld int32_type_register(type_description_cref head)
{
    int32_type_description = malloc(sizeof(type_description_type));
    int32_type_description->scheme = int32_type_scheme;
    int32_type_description->size = sizeof(int32_t);
    int32_type_description->next = head;

    return int32_type_description;
}

datum_hld int32_datum_construct(int32_t value)
{
    void_hld bytes = int32_to_ptr(value);
    return datum_construct(int32_type_description, &bytes);
}

int32_t int32_datum_extract(datum_cref datum)
{
    assert(datum->description == int32_type_description);
    return ptr_to_int32(datum->bytes);
}
