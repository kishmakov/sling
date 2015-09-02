#include "types/double.h"

#include <stdlib.h>

static type_description_ptr double_type_description = NULL;

static char* double_type_scheme = "{\"double\": 1}";

void register_double_type(type_description_ptr* head) {
    double_type_description = malloc(sizeof(type_description_type));
    double_type_description->scheme = double_type_scheme;
    double_type_description->size = sizeof(double);
    double_type_description->next = *head;

    *head = double_type_description;
}

datum_ptr create_double_datum(double value) {
    return create_datum(double_type_description, (const void*) &value);
}
