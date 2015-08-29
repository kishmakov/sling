#include "datum/int32.h"

#include <memory.h>
#include <stdlib.h>

static datum_description_ptr int32_datum_description = NULL;

static char* int32_datum_scheme = "{\"int32\": 1}";

void register_int32_datum() {
    int32_datum_description = malloc(sizeof(datum_description_type));
    int32_datum_description->scheme = int32_datum_scheme;
    int32_datum_description->size = sizeof(int32_t);
    int32_datum_description->next = datum_descriptions_head;
    datum_descriptions_head = int32_datum_description;
}

datum_ptr create_int32_datum(int32_t value) {
    datum_ptr datum_ptr = malloc(sizeof(datum_type));
    datum_ptr->description = int32_datum_description;
    datum_ptr->bytes = malloc(int32_datum_description->size);
    memcpy(datum_ptr->bytes, (const void*) &value, int32_datum_description->size);
    return datum_ptr;
}
