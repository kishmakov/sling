#include "basic_transforms_tests.h"

#include "unit_tests_main.h"

#include "sling_init.h"
#include "types/int32.h"
#include "types/double.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_to_double.h"

#include <math.h>

const int32_t vs[] = {-1073741823, -1023, 0, 1023, 1073741823};
const int N = sizeof(vs) / sizeof(int32_t);

void run_int32_addition_tests(void **state)
{
    (void) state;

    transform_ptr addition = int32_addition_construct();

    for (int i = 0; i + 1 < N; i++)
        for (int j = i + 1; j < N; j++) {
            context_ptr input = context_construct(2, 0);
            input->data[0] = int32_datum_construct(vs[i]);
            input->data[1] = int32_datum_construct(vs[j]);

            context_ptr output = transform_function(addition, &input);

            assert_null(input);
            assert_int_equal(output->data_size, 1);

            int32_t vres = int32_datum_extract(output->data[0]);
            datum_destruct(&(output->data[0]));
            context_destruct(&output);

            assert_int_equal(vs[i] + vs[j], vres);
        }

    transform_destruct(&addition);
    assert_null(addition);
}

void run_int32_duplicator_tests(void **state)
{
    (void) state;

    transform_ptr duplicator = int32_duplicator_construct();

    for (int i = 0; i < N; i++) {
        context_ptr input = context_construct(1, 0);
        input->data[0] = int32_datum_construct(vs[i]);

        context_ptr output = transform_function(duplicator, &input);

        assert_null(input);
        assert_int_equal(output->data_size, 2);

        int32_t v1 = int32_datum_extract(output->data[0]);
        int32_t v2 = int32_datum_extract(output->data[1]);
        datum_destruct(&(output->data[0]));
        datum_destruct(&(output->data[1]));
        context_destruct(&output);

        assert_int_equal(vs[i], v1);
        assert_int_equal(vs[i], v2);
    }

    transform_destruct(&duplicator);
    assert_null(duplicator);
}

void run_int32_to_double_tests(void **state)
{
    (void) state;

    transform_ptr converter = int32_to_double_construct();

    for (int i = 0; i < N; i++) {
        context_ptr input = context_construct(1, 0);
        input->data[0] = int32_datum_construct(vs[i]);
        context_ptr output = transform_function(converter, &input);
        assert_null(input);
        assert_int_equal(output->data_size, 1);

        double vd = double_datum_extract(output->data[0]);
        datum_destruct(&(output->data[0]));
        context_destruct(&output);
        assert_true(fabs(vd - (double) vs[i]) < 1e-10);
    }

    transform_destruct(&converter);
    assert_null(converter);
}

