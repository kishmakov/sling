#include "datum/int32.h"

#include <assert.h>
#include <stdio.h>
#include <memory.h>

datum_ptr sum_int32_datums(datum_ptr* datum_holder_1, datum_ptr* datum_holder_2)
{
    int32_t value1;
    memcpy((void*) &value1, (*datum_holder_1)->bytes, sizeof(int32_t));
    int32_t value2;
    memcpy((void*) &value2, (*datum_holder_2)->bytes, sizeof(int32_t));

    remove_datum(datum_holder_1);
    remove_datum(datum_holder_2);

    return create_int32_datum(value1 + value2);
}

int main(int argc, char ** argv)
{
    data_descriptions();

    datum_ptr d1 = create_int32_datum(1023);
    datum_ptr d2 = create_int32_datum(10000);

    datum_ptr ds = sum_int32_datums(&d1, &d2);

    assert(d1 == NULL && d2 == NULL);

    int32_t res = 0;
    memcpy((void*) &res, ds->bytes, sizeof(int32_t));

    printf("1023 + 10000 = %d\n", res);
    return 0;
}