#include "transform_description.h"

#include "transforms/int32_duplicator.h"

#include <stdlib.h>

transform_description_ptr transform_descriptions_head = NULL;

transform_description_ptr transform_descriptions()
{
    if (transform_descriptions_head == NULL) {
        int32_duplicator_register(&transform_descriptions_head);
    }

    return transform_descriptions_head;
}
