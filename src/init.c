#include "init.h"

#include "diagnostic.h"
#include "transform_description.h"
#include "type_description.h"


void init()
{
#ifdef DIAGNOSTIC_MODE
    printf("Diagnotic mode is turn on.\n");
#endif

    init_types_descriptions();
    init_transforms_descriptions();
}