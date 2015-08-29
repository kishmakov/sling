#include "datum/description.h"

#include "datum/int32.h"

#include <stdlib.h>

datum_description_ptr datum_descriptions_head = NULL;

datum_description_ptr datum_descriptions()
{
    if (datum_descriptions_head == NULL) {
        register_int32_datum(&datum_descriptions_head);
    }

    return datum_descriptions_head;
}

