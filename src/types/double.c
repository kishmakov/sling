#include "types/double.h"

#include <assert.h>
#include <stdlib.h>

static type_description_ptr double_type_description = NULL;

static char* double_type_scheme = "{\"double\": 1}";

void double_type_register(type_description_ptr* head) {
    double_type_description = malloc(sizeof(type_description_type));
    double_type_description->scheme = double_type_scheme;
    double_type_description->size = sizeof(double);
    double_type_description->next = *head;

    *head = double_type_description;
}

datum_ptr double_datum_construct(double value) {
    return datum_construct(double_type_description, (const void*) &value);
}

double double_datum_extract(datum_cptr datum)
{
    assert(datum->description == double_type_description);

    double result;
    datum_extract_value(datum, &result);
    return result;
}
