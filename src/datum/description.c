#include "datum/description.h"

#include "datum/int32.h"

#include <stdlib.h>

datum_description_ptr datum_descriptions_head = NULL;

void initialize_datum_descriptions()
{
    register_int32_datum();
}