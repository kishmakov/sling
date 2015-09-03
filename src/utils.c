#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* format = "{\"transforms\": [%s], \"data\": [%s]}";

char* scheme_description(const char * data, const char * transforms)
{
    char* result = malloc(strlen(format) + strlen(data) + strlen(transforms));
    sprintf(result, format, data, transforms);
    return result;
}
