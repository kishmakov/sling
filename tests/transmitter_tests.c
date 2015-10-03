#include "transmitter_tests.h"

#include "unit_tests_main.h"

#include "context.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_to_double.h"
#include "transmitter.h"
#include "types/int32.h"

static void trie_move_test(void)
{
    // 1

    context_hld c1_src = context_construct(2, 1);
    context_hld c1_dst = context_construct(0, 0);
    transmitter_hld t1 = transmitter_construct(1, 1);
    t1->data_maps[0] = (id_map_type) {.from=0, .to=0};
    t1->transforms_maps[0] = (id_map_type) {.from=0, .to=0};

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
    transmitter_hld t2 = transmitter_construct(2, 2);
    t2->data_maps[0] = (id_map_type) {.from=1, .to=1};
    t2->data_maps[1] = (id_map_type) {.from=2, .to=0};
    t2->transforms_maps[0] = (id_map_type) {.from=2, .to=1};
    t2->transforms_maps[1] = (id_map_type) {.from=1, .to=0};

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

static void trie_copy_test(void)
{
    // 1

    context_hld c1_src = context_construct(2, 1);
    c1_src->data[0] = int32_datum_construct(1);
    c1_src->data[1] = int32_datum_construct(2);
    c1_src->transforms[0] = int32_duplicator_construct(NULL);
    context_hld c1_dst = context_construct(0, 0);
    transmitter_hld t1 = transmitter_construct(1, 1);
    t1->data_maps[0] = (id_map_type) {.from=0, .to=0};
    t1->transforms_maps[0] = (id_map_type) {.from=0, .to=0};

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
    c2_src->transforms[0] = int32_addition_construct(NULL);
    c2_src->transforms[1] = int32_to_double_construct(NULL);
    c2_src->transforms[2] = int32_duplicator_construct(NULL);
    context_hld c2_dst = context_construct(0, 0);
    transmitter_hld t2 = transmitter_construct(2, 2);
    t2->data_maps[0] = (id_map_type) {.from=1, .to=1};
    t2->data_maps[1] = (id_map_type) {.from=2, .to=0};
    t2->transforms_maps[0] = (id_map_type) {.from=2, .to=1};
    t2->transforms_maps[1] = (id_map_type) {.from=1, .to=0};

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

void run_transmitter_tests(void **state)
{
    (void) state;

    trie_move_test();
    trie_copy_test();
}
