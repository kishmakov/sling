#include "basic_minds_tests.h"

#include "unit_tests_main.h"
#include "tests_tools.h"

#include "minds/int32_compare.h"
#include "sling_init.h"
#include "types/int32.h"

#include <math.h>

void run_int32_compare_tests(void **state)
{
    (void) state;

    mind_ptr compare = int32_compare_construct();

    for (int i = 0; i + 1 < N; i++)
        for (int j = i + 1; j < N; j++) {
            context_ptr input = context_construct(2, 0);
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
