#include "mind_description.h"

#include <stdlib.h>

mind_description_ptr minds_descriptions_head = NULL;

mind_description_ptr minds_descriptions()
{
    if (minds_descriptions_head == NULL) {
        // TODO: insert mind descriptions
    }

    return minds_descriptions_head;
}

void init_minds_descriptions()
{
    minds_descriptions();
}