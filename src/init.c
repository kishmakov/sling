#include "init.h"

#include "transform_description.h"
#include "type_description.h"
#include "utils/diagnostics.h"
#include "utils/log.h"

void init()
{
    init_logging();

#ifdef DIAGNOSTIC_MODE
    LOG_INFO("Diagnostic mode is turned on.");
#endif

    init_types_descriptions();
    init_transforms_descriptions();
}