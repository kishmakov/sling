#pragma once

#include <stdint.h>

typedef struct datum_description_type* datum_description_ptr;

struct datum_description_type {
    char * scheme;
    uint64_t size;
    datum_description_ptr next;
};

typedef struct datum_description_type datum_description_type;

extern datum_description_ptr datum_descriptions_head;

void initialize_datum_descriptions();
