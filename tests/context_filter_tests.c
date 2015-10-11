#include "context_filter_tests.h"

#include "tests_tools.h"
#include "unit_tests_main.h"

#include "context.h"
#include "transforms/context_filter.h"
#include "transforms/int32_gen.h"
#include "types/int32.h"

void run_context_filter_tests(void **state)
{
    (void) state;

    context_hld input = context_construct(4, 5);
    input->data[0] = int32_datum_construct(1);
    input->data[1] = int32_datum_construct(2);
    input->data[2] = int32_datum_construct(3);
    input->data[3] = int32_datum_construct(4);
    input->transforms[0] = build_int32_gen(5);
    input->transforms[1] = build_int32_gen(6);
    input->transforms[2] = build_int32_gen(7);
    input->transforms[3] = build_int32_gen(8);
    input->transforms[4] = build_int32_gen(9);

    uint32_t data[][2] = {{1, 1}, {3, 0}};
    uint32_t transforms[][2] = {{3, 2}, {1, 1}};

    transform_hld filter_pre = MACRO_BUILD_CONTEXT_FILTER(data, transforms);
    transform_hld filter = transform_copy(filter_pre);

    transform_destruct(&filter_pre);
    assert_null(filter_pre);

    context_hld output = transform_function(filter, &input);

    transform_destruct(&filter);
    assert_null(filter);
    assert_null(input);

    assert_int_equal(output->data_size, 2);
    assert_int_equal(output->transforms_size, 3);

    assert_int_equal(int32_datum_extract(output->data[0]), 4);
    assert_int_equal(int32_datum_extract(output->data[1]), 2);
    assert_int_equal(test_get_int(output->transforms[1]), 6);
    assert_int_equal(test_get_int(output->transforms[2]), 8);

    datum_destruct(&(output->data[0]));
    datum_destruct(&(output->data[1]));
    transform_destruct(&(output->transforms[1]));
    transform_destruct(&(output->transforms[2]));
    context_destruct(&output); assert_null(output);
}
