#include "datum/int32.h"

#include <stdlib.h>

static datum_description_ptr int32_datum_description = NULL;

static char* int32_datum_scheme = "{\"int32\": 1}";

void register_int32_datum(datum_description_ptr* head) {
    int32_datum_description = malloc(sizeof(datum_description_type));
    int32_datum_description->scheme = int32_datum_scheme;
    int32_datum_description->size = sizeof(int32_t);
    int32_datum_description->next = *head;

    *head = int32_datum_description;
}

datum_ptr create_int32_datum(int32_t value) {
    return create_datum(int32_datum_description, (const void*) &value);
}
