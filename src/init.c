#include "init.h"

#include "transform_description.h"
#include "type_description.h"
#include "utils/diagnostic.h"
#include "utils/log.h"

void init()
{
#ifdef DIAGNOSTIC_MODE
    LOG_INFO("Diagnostic mode is turned on.");
#endif

    init_types_descriptions();
    init_transforms_descriptions();
}