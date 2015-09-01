#pragma once

#include <stdint.h>

typedef struct datum_description_type datum_description_type;
typedef datum_description_type* datum_description_ptr;

struct datum_description_type {
    char * scheme;
    uint64_t size;
    datum_description_ptr next;
};

datum_description_ptr data_descriptions();

