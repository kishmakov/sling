#include "init.h"

#include "diagnostic.h"
#include "log.h"
#include "transform_description.h"
#include "type_description.h"

void init()
{
#ifdef DIAGNOSTIC_MODE
    LOG_INFO("Diagnostic mode is turn on.");
#endif

    init_types_descriptions();
    init_transforms_descriptions();
}