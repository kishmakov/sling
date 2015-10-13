#include "transmitter_tests.h"

#include "unit_tests_main.h"

#include "context.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_to_double.h"
#include "transmitter.h"
#include "types/int32.h"

static void transmitter_move_test(void)
{
    // 1

    context_hld c1_src = context_construct(2, 1);
    context_hld c1_dst = context_construct(0, 0);

    uint32_t data1[][2] = {{0, 0}};
    uint32_t transforms1[][2] = {{0, 0}};
    transmitter_hld t1 = MACRO_BUILD_TRANSMITTER(data1, transforms1);

    transmit_move(t1, c1_dst, c1_src);

    assert_int_equal(c1_dst->data_size, 1);
    assert_int_equal(c1_dst->transforms_size, 1);
    assert_ptr_equal(c1_dst->data[0], NULL);
    assert_ptr_equal(c1_dst->transforms[0], NULL);

    context_destruct(&c1_src); assert_null(c1_src);
    context_destruct(&c1_dst); assert_null(c1_dst);
    transmitter_destruct(&t1); assert_null(t1);

    // 2

    context_hld c2_src = context_construct(4, 3);
    c2_src->data[0] = (void*) 1;
    c2_src->data[1] = (void*) 2;
    c2_src->data[2] = (void*) 3;
    c2_src->data[3] = (void*) 4;
    c2_src->transforms[0] = (void*) 5;
    c2_src->transforms[1] = (void*) 6;
    c2_src->transforms[2] = (void*) 7;
    context_hld c2_dst = context_construct(0, 0);

    uint32_t data2[][2] = {{1, 1}, {0, 2}};
    uint32_t transforms2[][2] = {{1, 2}, {0, 1}};
    transmitter_hld t2 = MACRO_BUILD_TRANSMITTER(data2, transforms2);

    transmit_move(t2, c2_dst, c2_src);

    assert_int_equal(c2_dst->data_size, 2);
    assert_int_equal(c2_dst->transforms_size, 2);

    assert_ptr_equal(c2_src->data[0], (void*) 1);
    assert_ptr_equal(c2_src->data[1], (void*) 0);
    assert_ptr_equal(c2_src->data[2], (void*) 0);
    assert_ptr_equal(c2_src->data[3], (void*) 4);
    assert_ptr_equal(c2_src->transforms[0], (void*) 5);
    assert_ptr_equal(c2_src->transforms[1], (void*) 0);
    assert_ptr_equal(c2_src->transforms[2], (void*) 0);

    assert_ptr_equal(c2_dst->data[0], (void*) 3);
    assert_ptr_equal(c2_dst->data[1], (void*) 2);
    assert_ptr_equal(c2_dst->transforms[0], (void*) 6);
    assert_ptr_equal(c2_dst->transforms[1], (void*) 7);

    memset(c2_src->data, 0, sizeof(void*) * c2_src->data_size);
    memset(c2_dst->data, 0, sizeof(void*) * c2_dst->data_size);
    memset(c2_src->transforms, 0, sizeof(void*) * c2_src->transforms_size);
    memset(c2_dst->transforms, 0, sizeof(void*) * c2_dst->transforms_size);

    context_destruct(&c2_src); assert_null(c2_src);
    context_destruct(&c2_dst); assert_null(c2_dst);
    transmitter_destruct(&t2); assert_null(t2);
}

static void transmitter_copy_test(void)
{
    // 1

    context_hld c1_src = context_construct(2, 1);
    c1_src->data[0] = int32_datum_construct(1);
    c1_src->data[1] = int32_datum_construct(2);
    c1_src->transforms[0] = build_int32_duplicator();
    context_hld c1_dst = context_construct(0, 0);
    uint32_t data1[][2] = {{0, 0}};
    uint32_t transforms1[][2] = {{0, 0}};
    transmitter_hld t1 = MACRO_BUILD_TRANSMITTER(data1, transforms1);

    transmit_copy(t1, c1_dst, c1_src);

    assert_int_equal(c1_dst->data_size, 1);
    assert_int_equal(c1_dst->transforms_size, 1);
    assert_int_equal(int32_datum_extract(c1_src->data[0]), 1);
    assert_string_equal(c1_src->transforms[0]->description->profile(NULL), "int32_dupl");

    datum_destruct(&(c1_dst->data[0]));
    datum_destruct(&(c1_src->data[0]));
    datum_destruct(&(c1_src->data[1]));
    transform_destruct(&(c1_dst->transforms[0]));
    transform_destruct(&(c1_src->transforms[0]));

    context_destruct(&c1_src); assert_null(c1_src);
    context_destruct(&c1_dst); assert_null(c1_dst);
    transmitter_destruct(&t1); assert_null(t1);

    // 2

    context_hld c2_src = context_construct(4, 3);
    c2_src->data[0] = int32_datum_construct(1);
    c2_src->data[1] = int32_datum_construct(2);
    c2_src->data[2] = int32_datum_construct(3);
    c2_src->data[3] = int32_datum_construct(4);
    c2_src->transforms[0] = build_int32_addition();
    c2_src->transforms[1] = build_int32_to_double();
    c2_src->transforms[2] = build_int32_duplicator();
    context_hld c2_dst = context_construct(0, 0);

    uint32_t data2[][2] = {{1, 1}, {0, 2}};
    uint32_t transforms2[][2] = {{1, 2}, {0, 1}};
    transmitter_hld t2 = MACRO_BUILD_TRANSMITTER(data2, transforms2);

    transmit_copy(t2, c2_dst, c2_src);

    assert_int_equal(c2_dst->data_size, 2);
    assert_int_equal(c2_dst->transforms_size, 2);

    assert_int_equal(int32_datum_extract(c2_src->data[0]), 1);
    assert_int_equal(int32_datum_extract(c2_src->data[1]), 2);
    assert_int_equal(int32_datum_extract(c2_src->data[2]), 3);
    assert_int_equal(int32_datum_extract(c2_src->data[3]), 4);
    assert_string_equal(c2_src->transforms[0]->description->profile(NULL), "int32_add");
    assert_string_equal(c2_src->transforms[1]->description->profile(NULL), "int32_to_double");
    assert_string_equal(c2_src->transforms[2]->description->profile(NULL), "int32_dupl");

    assert_int_equal(int32_datum_extract(c2_dst->data[0]), 3);
    assert_ptr_equal(int32_datum_extract(c2_dst->data[1]), 2);
    assert_string_equal(c2_dst->transforms[0]->description->profile(NULL), "int32_to_double");
    assert_string_equal(c2_dst->transforms[1]->description->profile(NULL), "int32_dupl");

    datum_destruct(&(c2_dst->data[0]));
    datum_destruct(&(c2_dst->data[1]));
    datum_destruct(&(c2_src->data[0]));
    datum_destruct(&(c2_src->data[1]));
    datum_destruct(&(c2_src->data[2]));
    datum_destruct(&(c2_src->data[3]));

    transform_destruct(&(c2_dst->transforms[0]));
    transform_destruct(&(c2_dst->transforms[1]));
    transform_destruct(&(c2_src->transforms[0]));
    transform_destruct(&(c2_src->transforms[1]));
    transform_destruct(&(c2_src->transforms[2]));

    context_destruct(&c2_src); assert_null(c2_src);
    context_destruct(&c2_dst); assert_null(c2_dst);
    transmitter_destruct(&t2); assert_null(t2);
}

static void transmitter_dupl_test(void)
{
    uint32_t data[][2] = {{1, 1}, {0, 2}};
    uint32_t transforms[][2] = {{1, 2}, {0, 1}, {2, 3}};
    transmitter_hld src = MACRO_BUILD_TRANSMITTER(data, transforms);

    transmitter_hld dst = transmitter_copy(src);

    assert_int_equal(src->data_maps_size, dst->data_maps_size);
    assert_int_equal(src->transforms_maps_size, dst->transforms_maps_size);

    for (int id = 0; id < src->data_maps_size; id++) {
        assert_int_equal(src->data_maps[id].from, dst->data_maps[id].from);
        assert_int_equal(src->data_maps[id].to, dst->data_maps[id].to);
    }

    for (int id = 0; id < src->transforms_maps_size; id++) {
        assert_int_equal(src->transforms_maps[id].from, dst->transforms_maps[id].from);
        assert_int_equal(src->transforms_maps[id].to, dst->transforms_maps[id].to);
    }

    transmitter_destruct(&src); assert_null(src);
    transmitter_destruct(&dst); assert_null(dst);
}


void run_transmitter_tests(void **state)
{
    (void) state;

    transmitter_move_test();
    transmitter_copy_test();
    transmitter_dupl_test();
}
