#include "basic_transforms_tests.h"

#include "tests_tools.h"
#include "unit_tests_main.h"

#include "sling_init.h"
#include "types/int32.h"
#include "types/double.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_mult_by.h"
#include "transforms/int32_to_double.h"

#include <math.h>

void run_int32_addition_tests(void **state)
{
    (void) state;

    transform_hld addition = int32_addition_construct(NULL);

    for (int i = 0; i + 1 < N; i++)
        for (int j = i + 1; j < N; j++) {
            context_hld input = context_construct(2, 0);
            input->data[0] = int32_datum_construct(vs[i]);
            input->data[1] = int32_datum_construct(vs[j]);

            context_hld output = transform_function(addition, &input);

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

    transform_hld duplicator = int32_duplicator_construct(NULL);

    for (int i = 0; i < N; i++) {
        context_hld input = context_construct(1, 0);
        input->data[0] = int32_datum_construct(vs[i]);

        context_hld output = transform_function(duplicator, &input);

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

    transform_hld converter = int32_to_double_construct(NULL);

    for (int i = 0; i < N; i++) {
        context_hld input = context_construct(1, 0);
        input->data[0] = int32_datum_construct(vs[i]);
        context_hld output = transform_function(converter, &input);
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

void run_int32_mult_by_tests(void **state)
{
    static const int32_t nums[] = {-173741823, -1023, 0, 1023, 173741823};
    static const int32_t mults[] = {-10, -2, 2, 4, 13};

    (void) state;


    for (int i = 0; i < sizeof(mults) / 4; i++) {
        transform_hld mult_by = int32_mult_by_construct((void*) &mults[i]);
        for (int j = 0; j < sizeof(nums) / 4; j++) {
            context_hld input = context_construct(1, 0);
            input->data[0] = int32_datum_construct(nums[j]);

            context_hld output = transform_function(mult_by, &input);

            assert_null(input);
            assert_int_equal(output->data_size, 1);

            int32_t vres = int32_datum_extract(output->data[0]);
            datum_destruct(&(output->data[0]));
            context_destruct(&output);

            assert_int_equal(mults[i] * nums[j], vres);
        }
        transform_destruct(&mult_by);
        assert_null(mult_by);
    }


}