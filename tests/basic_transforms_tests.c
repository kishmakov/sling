#include "basic_transforms_tests.h"

#include "unit_tests_main.h"

#include "sling_init.h"
#include "types/int32.h"
#include "types/double.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_to_double.h"

#include <math.h>

void run_int32_addition_tests(void **state)
{
    (void) state;

    int32_t v0 = 1023;
    int32_t v1 = 10000;

    context_ptr input = context_create(2, 0);
    input->data[0] = int32_datum_create(v0);
    input->data[1] = int32_datum_create(v1);

    transform_ptr addition = int32_addition_create();

    context_ptr output = int32_addition_func(addition, &input);

    assert_null(input);
    assert_int_equal(output->data_size, 1);

    int32_t vres = int32_datum_extract(output->data[0]);
    datum_delete(&(output->data[0]));
    context_delete(&output);

    assert_int_equal(v0 + v1, vres);
}

void run_int32_duplicator_tests(void **state)
{
    (void) state;

    int32_t v = 239;

    context_ptr input = context_create(1, 0);
    input->data[0] = int32_datum_create(v);

    transform_ptr duplicator = int32_duplicator_create();
    context_ptr output = int32_duplicator_func(duplicator, &input);

    assert_null(input);
    assert_int_equal(output->data_size, 2);

    int32_t v1 = int32_datum_extract(output->data[0]);
    int32_t v2 = int32_datum_extract(output->data[1]);
    datum_delete(&(output->data[0]));
    datum_delete(&(output->data[1]));
    context_delete(&output);

    assert_int_equal(v, v1);
    assert_int_equal(v, v2);
}

void run_int32_to_double_tests(void **state)
{
    (void) state;

    int32_t vi = 239;

    context_ptr input = context_create(1, 0);
    input->data[0] = int32_datum_create(vi);

    transform_ptr converter = int32_to_double_create();

    context_ptr output = int32_to_double_func(converter, &input);

    assert_null(input);
    assert_int_equal(output->data_size, 1);

    double vd = double_datum_extract(output->data[0]);
    datum_delete(&(output->data[0]));
    context_delete(&output);
    assert_true(fabs(vd - (double) vi) < 1e-10);
}

