#include "datum/datum.h"

#include <stdlib.h>

void remove_datum(datum_ptr* datum_holder) {
    free((*datum_holder)->bytes);
    free(*datum_holder);
    *datum_holder = NULL;
};
