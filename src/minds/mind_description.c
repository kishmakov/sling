#include "mind_description.h"

#include "minds/int32_compare.h"
#include "minds/int32_sign.h"

#include <assert.h>
#include <stdlib.h>

mind_description_hld minds_descriptions_head = NULL;

mind_description_cref minds_descriptions()
{
    return minds_descriptions_head;
}

void init_minds_descriptions()
{
    assert(minds_descriptions_head == NULL);

    minds_descriptions_head = int32_compare_register(minds_descriptions_head);
    minds_descriptions_head = int32_sign_register(minds_descriptions_head);
}