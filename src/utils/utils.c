#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* context_format = "{\"data\": [%s], \"transforms\": [%s]}";

char* context_scheme(const char * data, const char * transforms)
{
    char* result = malloc(strlen(context_format) + strlen(data) + strlen(transforms));
    sprintf(result, context_format, data, transforms);
    return result;
}

char* decision_scheme(const char* alternatives[], const uint32_t alternatives_number)
{
    uint32_t needed_length = 5;
    for (uint32_t id = 0; id < alternatives_number; id++)
        needed_length += strlen(alternatives[id]) + 10;


    char* result = malloc(needed_length);
    sprintf(result, "{");

    char local_buffer[200];
    for (uint32_t id = 0; id < alternatives_number; id++) {
        sprintf(local_buffer, "\"%s\":%u", alternatives[id], id);
        strcat(result, local_buffer);

        strcat(result, (id + 1 < alternatives_number ? "," : "}"));
    }

    return result;
}
