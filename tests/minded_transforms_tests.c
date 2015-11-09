#include "minded_transforms_tests.h"

#include "tests_tools.h"
#include "unit_tests_main.h"

#include "minds/int32_sign.h"
#include "mt/minded_transform.h"
#include "mt/state.h"
#include "transforms/context_filter.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_gen.h"
#include "transforms/int32_mult_by.h"
#include "transforms/int32_multiplication.h"
#include "transmitter.h"
#include "types/int32.h"

#include <math.h>

static int32_t discriminant_classifier(int32_t a, int32_t b, int32_t c)
{
    if (a == 0)
        return b != 0 ? 1 : -1;

    int32_t discriminant = b * b - 4 * a * c;
    return discriminant > 0 ? 2 : (discriminant == 0 ? 1 : 0);
}

static transform_hld construct_discriminant_classifier()
{
    minded_transform_impl_hld impl = malloc(sizeof(minded_transform_impl_type));
    impl->minds = trie_construct();
    impl->transforms = trie_construct();

    trie_insert(impl->minds, "int32_sign", int32_sign_construct());
    {
        uint32_t d[][2] = {};
        uint32_t t[][2] = {};
        trie_insert(impl->transforms, "context_filter", MACRO_BUILD_CONTEXT_FILTER(d, t));
    }
    trie_insert(impl->transforms, "int32_dupl", build_int32_duplicator());
    trie_insert(impl->transforms, "int32_add", build_int32_addition());
    trie_insert(impl->transforms, "int32_gen_-1", build_int32_gen(-1));
    trie_insert(impl->transforms, "int32_gen_0", build_int32_gen(0));
    trie_insert(impl->transforms, "int32_gen_1", build_int32_gen(1));
    trie_insert(impl->transforms, "int32_gen_2", build_int32_gen(2));
    trie_insert(impl->transforms, "int32_mult", build_int32_multiplication());
    trie_insert(impl->transforms, "int32_mult_by_-4", build_int32_mult_by(-4));

    MACRO_VECTOR_ALLOCATE(impl->states, state_hld, 12);

    impl->states[0] = malloc(sizeof(state_type));
    impl->states[1] = malloc(sizeof(state_type));
    impl->states[2] = malloc(sizeof(state_type));
    impl->states[3] = malloc(sizeof(state_type));
    impl->states[4] = malloc(sizeof(state_type));
    impl->states[5] = malloc(sizeof(state_type));
    impl->states[6] = malloc(sizeof(state_type));
    impl->states[7] = malloc(sizeof(state_type));
    impl->states[8] = malloc(sizeof(state_type));
    impl->states[9] = malloc(sizeof(state_type));
    impl->states[10] = malloc(sizeof(state_type));
    impl->states[11] = malloc(sizeof(state_type));

    impl->start = impl->states[0];
    impl->finish = impl->states[1];

    { // 0: branch on A sign and doubling B if A != 0
        state_ref state = impl->states[0];

        uint32_t chk_data[][2] = {{0, 0}};
        uint32_t chk_transforms[][2] = {};
        state->download = MACRO_BUILD_TRANSMITTER(chk_data, chk_transforms);
        state->mind_profile = "int32_sign";
        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 3);

        uint32_t down_data0[][2] = {{0, 1}};
        uint32_t down_transforms0[][2] = {};
        uint32_t up_data0[][2] = {{1, 0}, {3, 1}};
        uint32_t up_transforms0[][2] = {};

        state->steps[0].transform_profile = "int32_dupl";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data0, down_transforms0);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data0, up_transforms0);
        state->steps[0].next_state = impl->states[7];

        state->steps[1].transform_profile = NULL;
        state->steps[1].download = NULL;
        state->steps[1].upload = NULL;
        state->steps[1].next_state = impl->states[2];

        uint32_t down_data2[][2] = {{0, 1}};
        uint32_t down_transforms2[][2] = {};
        uint32_t up_data2[][2] = {{1, 0}, {3, 1}};
        uint32_t up_transforms2[][2] = {};

        state->steps[2].transform_profile = "int32_dupl";
        state->steps[2].download = MACRO_BUILD_TRANSMITTER(down_data2, down_transforms2);
        state->steps[2].upload = MACRO_BUILD_TRANSMITTER(up_data2, up_transforms2);
        state->steps[2].next_state = impl->states[7];
    }

    { // 1: exit
        state_ref state = impl->states[1];
        state->download = NULL;
        state->mind_profile = NULL;
        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 0);
    }

    { // 2: branch on B sign
        state_ref state = impl->states[2];

        uint32_t chk_data[][2] = {{0, 1}};
        uint32_t chk_transforms[][2] = {};
        state->download = MACRO_BUILD_TRANSMITTER(chk_data, chk_transforms);
        state->mind_profile = "int32_sign";
        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 3);

        uint32_t down_data0[][2] = {{0, 0}, {1, 1}, {2, 2}};
        uint32_t down_transforms0[][2] = {};
        uint32_t up_data0[][2] = {};
        uint32_t up_transforms0[][2] = {};

        state->steps[0].transform_profile = "context_filter";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data0, down_transforms0);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data0, up_transforms0);
        state->steps[0].next_state = impl->states[3];

        uint32_t down_data1[][2] = {{0, 0}, {1, 1}, {2, 2}};
        uint32_t down_transforms1[][2] = {};
        uint32_t up_data1[][2] = {};
        uint32_t up_transforms1[][2] = {};

        state->steps[1].transform_profile = "context_filter";
        state->steps[1].download = MACRO_BUILD_TRANSMITTER(down_data1, down_transforms1);
        state->steps[1].upload = MACRO_BUILD_TRANSMITTER(up_data1, up_transforms1);
        state->steps[1].next_state = impl->states[4];

        uint32_t down_data2[][2] = {{0, 0}, {1, 1}, {2, 2}};
        uint32_t down_transforms2[][2] = {};
        uint32_t up_data2[][2] = {};
        uint32_t up_transforms2[][2] = {};

        state->steps[2].transform_profile = "context_filter";
        state->steps[2].download = MACRO_BUILD_TRANSMITTER(down_data2, down_transforms2);
        state->steps[2].upload = MACRO_BUILD_TRANSMITTER(up_data2, up_transforms2);
        state->steps[2].next_state = impl->states[3];
    }

    { // 3: prepare 1 as result
        state_ref state = impl->states[3];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_gen_1";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[1];
    }

    { // 4: prepare -1 as result
        state_ref state = impl->states[4];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_gen_-1";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[1];
    }

    { // 5: prepare 0 as result
        state_ref state = impl->states[5];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_gen_0";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[1];
    }

    { // 6: prepare 2 as result
        state_ref state = impl->states[6];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_gen_2";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[1];
    }

    { // 7: A,B,C,B -> A,B^2,C
        state_ref state = impl->states[7];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {{0, 1}, {1, 3}};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{1, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_mult";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[8];
    }

    { // 8: A,B^2,C -> AC,B^2
        state_ref state = impl->states[8];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {{0, 0}, {1, 2}};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_mult";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[9];
    }

    { // 9: AC,B^2 -> -4AC,B^2
        state_ref state = impl->states[9];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {{0, 0}};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_mult_by_-4";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[10];
    }

    { // 10: -4AC,B^2 -> B^2 - 4AC
        state_ref state = impl->states[10];

        state->download = NULL;
        state->mind_profile = NULL;

        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 1);

        uint32_t down_data[][2] = {{0, 0}, {1, 1}};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        state->steps[0].transform_profile = "int32_add";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[11];
    }

    { // 11: branch on discriminant sign
        state_ref state = impl->states[11];

        uint32_t chk_data[][2] = {{0, 0}};
        uint32_t chk_transforms[][2] = {};
        state->download = MACRO_BUILD_TRANSMITTER(chk_data, chk_transforms);
        state->mind_profile = "int32_sign";
        MACRO_VECTOR_ALLOCATE(state->steps, state_step_type, 3);

        uint32_t down_data0[][2] = {{0, 0}};
        uint32_t down_transforms0[][2] = {};
        uint32_t up_data0[][2] = {};
        uint32_t up_transforms0[][2] = {};

        state->steps[0].transform_profile = "context_filter";
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data0, down_transforms0);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data0, up_transforms0);
        state->steps[0].next_state = impl->states[5];

        uint32_t down_data1[][2] = {{0, 0}};
        uint32_t down_transforms1[][2] = {};
        uint32_t up_data1[][2] = {};
        uint32_t up_transforms1[][2] = {};

        state->steps[1].transform_profile = "context_filter";
        state->steps[1].download = MACRO_BUILD_TRANSMITTER(down_data1, down_transforms1);
        state->steps[1].upload = MACRO_BUILD_TRANSMITTER(up_data1, up_transforms1);
        state->steps[1].next_state = impl->states[3];

        uint32_t down_data2[][2] = {{0, 0}};
        uint32_t down_transforms2[][2] = {};
        uint32_t up_data2[][2] = {};
        uint32_t up_transforms2[][2] = {};

        state->steps[2].transform_profile = "context_filter";
        state->steps[2].download = MACRO_BUILD_TRANSMITTER(down_data2, down_transforms2);
        state->steps[2].upload = MACRO_BUILD_TRANSMITTER(up_data2, up_transforms2);
        state->steps[2].next_state = impl->states[6];
    }

    return build_minded_transform(&impl);
}

void run_discriminant_tests(void **state)
{
    (void) state;

    static const int32_t nums[] = {-239, -2, -1, 0, 1, 2, 239};

    transform_hld classifier = construct_discriminant_classifier();

    for (int ia = 0; ia < sizeof(nums) / 4; ia++)
        for (int ib = 0; ib < sizeof(nums) / 4; ib++)
            for (int ic = 0; ic < sizeof(nums) / 4; ic++) {
                context_hld input = context_construct(3, 0);
                input->data[0] = int32_datum_construct(nums[ia]);
                input->data[1] = int32_datum_construct(nums[ib]);
                input->data[2] = int32_datum_construct(nums[ic]);

                context_hld output = transform_function(classifier, &input);

                assert_null(input);
                assert_true(output->data_size > 0); // ToDo: must be 1
                int32_t vres = int32_datum_extract(output->data[0]);
                datum_destruct(&(output->data[0]));
                context_destruct(&output);

                assert_int_equal(vres, discriminant_classifier(nums[ia], nums[ib], nums[ic]));
            }

    transform_destruct(&classifier);
    assert_null(classifier);
}

