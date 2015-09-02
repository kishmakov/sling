#include "type_description.h"

#include "types/double.h"
#include "types/int32.h"

#include <stdlib.h>

type_description_ptr types_descriptions_head = NULL;

type_description_ptr types_descriptions()
{
    if (types_descriptions_head == NULL) {
        double_type_register(&types_descriptions_head);
        int32_type_register(&types_descriptions_head);
    }

    return types_descriptions_head;
}

