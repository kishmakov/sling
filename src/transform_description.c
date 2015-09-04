#include "transform_description.h"

#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"

#include <stdlib.h>

transform_description_ptr transforms_descriptions_head = NULL;

transform_description_ptr transforms_descriptions()
{
    if (transforms_descriptions_head == NULL) {
        int32_addition_register(&transforms_descriptions_head);
        int32_duplicator_register(&transforms_descriptions_head);
    }

    return transforms_descriptions_head;
}

void init_transforms_descriptions()
{
    transforms_descriptions();
}