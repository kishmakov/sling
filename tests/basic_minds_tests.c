#include "basic_minds_tests.h"

#include "unit_tests_main.h"
#include "tests_tools.h"

#include "minds/int32_compare.h"
#include "minds/int32_sign.h"
#include "sling_init.h"
#include "types/int32.h"

#include <math.h>

void run_int32_compare_tests(void **state)
{
    (void) state;

    mind_hld compare = int32_compare_construct();

    for (int i = 0; i  < N; i++)
        for (int j = 0; j < N; j++) {
            context_hld input = context_construct(2, 0);
            input->data[0] = int32_datum_construct(vs[i]);
            input->data[1] = int32_datum_construct(vs[j]);

            uint32_t result_needed = vs[i] < vs[j] ? 0 : (vs[i] == vs[j] ? 1 : 2);
            uint32_t result = mind_function(compare, &input);

            assert_null(input);
            assert_int_equal(result, result_needed);
        }

    mind_destruct(&compare);
    assert_null(compare);
}

void run_int32_sign_tests(void **state)
{
    (void) state;

    mind_hld sign = int32_sign_construct();

    for (int i = 0; i  < N; i++) {
        context_hld input = context_construct(1, 0);
        input->data[0] = int32_datum_construct(vs[i]);

        uint32_t result_needed = 1 + (vs[i] > 0) - (vs[i] < 0);
        uint32_t result = mind_function(sign, &input);

        assert_null(input);
        assert_int_equal(result, result_needed);
    }

    mind_destruct(&sign);
    assert_null(sign);
}
