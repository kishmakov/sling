#include "transforms/transform_description.h"

#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_mult_by.h"
#include "transforms/int32_to_double.h"

#include <assert.h>
#include <stdlib.h>

transform_description_hld transforms_descriptions_head = NULL;

transform_description_cref transforms_descriptions()
{
    return transforms_descriptions_head;
}

void init_transforms_descriptions()
{
    assert(transforms_descriptions_head == NULL);

    int32_addition_register(&transforms_descriptions_head);
    int32_duplicator_register(&transforms_descriptions_head);
    int32_mult_by_register(&transforms_descriptions_head);
    int32_to_double_register(&transforms_descriptions_head);
}

