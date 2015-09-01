#include "datum/description.h"

#include "datum/double.h"
#include "datum/int32.h"

#include <stdlib.h>

datum_description_ptr data_descriptions_head = NULL;

datum_description_ptr data_descriptions()
{
    if (data_descriptions_head == NULL) {
        register_double_datum(&data_descriptions_head);
        register_int32_datum(&data_descriptions_head);
    }

    return data_descriptions_head;
}

