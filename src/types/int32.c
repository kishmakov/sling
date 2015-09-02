#include "types/int32.h"

#include <stdlib.h>

static type_description_ptr int32_type_description = NULL;

static char* int32_type_scheme = "{\"int32\": 1}";

void register_int32_type(type_description_ptr* head) {
    int32_type_description = malloc(sizeof(type_description_type));
    int32_type_description->scheme = int32_type_scheme;
    int32_type_description->size = sizeof(int32_t);
    int32_type_description->next = *head;

    *head = int32_type_description;
}

datum_ptr create_int32_datum(int32_t value) {
    return create_datum(int32_type_description, (const void*) &value);
}
