#include "datum/double.h"

#include <stdlib.h>

static datum_description_ptr double_datum_description = NULL;

static char* double_datum_scheme = "{\"double\": 1}";

void register_double_datum(datum_description_ptr* head) {
    double_datum_description = malloc(sizeof(datum_description_type));
    double_datum_description->scheme = double_datum_scheme;
    double_datum_description->size = sizeof(double);
    double_datum_description->next = *head;

    *head = double_datum_description;
}

datum_ptr create_double_datum(double value) {
    return create_datum(double_datum_description, (const void*) &value);
}
