#include "context.h"
#include "init.h"
#include "transforms/int32_duplicator.h"
#include "types/int32.h"

#include <assert.h>
#include <stdio.h>
#include <memory.h>

datum_ptr sum_int32_datums(datum_ptr* datum_holder_1, datum_ptr* datum_holder_2)
{
    int32_t value1 = int32_datum_extract(*datum_holder_1);
    int32_t value2 = int32_datum_extract(*datum_holder_2);

    datum_remove(datum_holder_1);
    datum_remove(datum_holder_2);

    return int32_datum_create(value1 + value2);
}

void test1()
{
    int32_t v1 = 1023;
    int32_t v2 = 10000;

    datum_ptr d1 = int32_datum_create(v1);
    datum_ptr d2 = int32_datum_create(v2);

    datum_ptr ds = sum_int32_datums(&d1, &d2);

    assert(d1 == NULL && d2 == NULL);

    int32_t res = int32_datum_extract(ds);
    datum_remove(&ds);

    printf("%d = %d + %d =?= %d\n", v1 + v2, v1, v2, res);
}

void test2()
{
    int32_t v = 239;

    context_ptr input = context_create(1, 0);
    input->data[0] = int32_datum_create(v);

    transform_ptr duplicator = int32_duplicator_create();

    context_ptr output = int32_duplicator_func(duplicator, input);

    assert(output->data_size == 2);

    int32_t v1 = int32_datum_extract(output->data[0]);
    int32_t v2 = int32_datum_extract(output->data[1]);

    printf("%d -> {%d, %d}\n", v, v1, v2);
}

int main(int argc, char ** argv)
{
    init();

    test1();
    test2();

    return 0;
}