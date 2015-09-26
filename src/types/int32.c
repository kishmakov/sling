#include "types/int32.h"

#include <assert.h>
#include <stdlib.h>

static type_description_ptr int32_type_description = NULL;

static char* int32_type_scheme = "{\"int32\": 1}";

type_description_ptr int32_type_register(type_description_cptr head)
{
    int32_type_description = malloc(sizeof(type_description_type));
    int32_type_description->scheme = int32_type_scheme;
    int32_type_description->size = sizeof(int32_t);
    int32_type_description->next = head;

    return int32_type_description;
}

datum_ptr int32_datum_construct(int32_t value)
{
    return datum_construct(int32_type_description, (const void*) &value);
}

int32_t int32_datum_extract(datum_cptr datum)
{
    assert(datum->description == int32_type_description);

    int32_t result;
    datum_extract_value(datum, &result);
    return result;
}
