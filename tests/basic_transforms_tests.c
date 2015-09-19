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

    const int32_t vs[] = {-1073741823, -1023, 0, 1023, 1073741823};
    const int N = sizeof(vs) / sizeof(int32_t);
    transform_ptr addition = int32_addition_construct();

    for (int i = 0; i + 1 < N; i++)
        for (int j = i + 1; j < N; j++) {
            context_ptr input = context_construct(2, 0);
            input->data[0] = int32_datum_construct(vs[i]);
            input->data[1] = int32_datum_construct(vs[j]);

            context_ptr output = int32_addition_function(addition, &input);

            assert_null(input);
            assert_int_equal(output->data_size, 1);

            int32_t vres = int32_datum_extract(output->data[0]);
            datum_destruct(&(output->data[0]));
            context_destruct(&output);

            assert_int_equal(vs[i] + vs[j], vres);
        }

    // transform_destruct(&addition);
    // assert_null(addition);
}

void run_int32_duplicator_tests(void **state)
{
    (void) state;

    int32_t v = 239;

    context_ptr input = context_construct(1, 0);
    input->data[0] = int32_datum_construct(v);

    transform_ptr duplicator = int32_duplicator_construct();
    context_ptr output = transform_function(duplicator, &input);

    assert_null(input);
    assert_int_equal(output->data_size, 2);

    int32_t v1 = int32_datum_extract(output->data[0]);
    int32_t v2 = int32_datum_extract(output->data[1]);
    datum_destruct(&(output->data[0]));
    datum_destruct(&(output->data[1]));
    context_destruct(&output);

    assert_int_equal(v, v1);
    assert_int_equal(v, v2);

    transform_destruct(&duplicator);
    assert_null(duplicator);
}

void run_int32_to_double_tests(void **state)
{
    (void) state;

    int32_t vi = 239;

    context_ptr input = context_construct(1, 0);
    input->data[0] = int32_datum_construct(vi);

    transform_ptr converter = int32_to_double_construct();

    context_ptr output = int32_to_double_function(converter, &input);

    assert_null(input);
    assert_int_equal(output->data_size, 1);

    double vd = double_datum_extract(output->data[0]);
    datum_destruct(&(output->data[0]));
    context_destruct(&output);
    assert_true(fabs(vd - (double) vi) < 1e-10);
}

