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
#include "transmitter.h"
#include "types/int32.h"

#include <math.h>

static int32_t discriminant_classifier(int32_t a, int32_t b, int32_t c)
{
    if (a == 0)
        return b != 0 ? 1 : (c == 0 ? -1 : 0);

    int32_t discriminant = b * b - 4 * a * c;
    return discriminant > 0 ? 2 : (discriminant == 0 ? 1 : 0);
}

static transform_hld construct_discriminant_classifier()
{
    minded_transform_impl_hld impl = malloc(sizeof(minded_transform_impl_type));
    impl->minds = NULL;
    impl->transforms = NULL;

    trie_insert(&(impl->minds), "int32_sign", int32_sign_construct());
    {
        uint32_t d[][2] = {};
        uint32_t t[][2] = {};
        trie_insert(&(impl->transforms), "context_filter", MACRO_BUILD_CONTEXT_FILTER(d, t));
    }
    trie_insert(&(impl->transforms), "int32_dupl", build_int32_duplicator());
    trie_insert(&(impl->transforms), "int32_add", build_int32_addition());
    trie_insert(&(impl->transforms), "int32_gen_-1", build_int32_gen(-1));
    trie_insert(&(impl->transforms), "int32_gen_0", build_int32_gen(0));
    trie_insert(&(impl->transforms), "int32_gen_1", build_int32_gen(1));
    trie_insert(&(impl->transforms), "int32_gen_2", build_int32_gen(2));
    trie_insert(&(impl->transforms), "int32_mult_by_-4", build_int32_mult_by(-4));

    MACRO_VECTOR_ALLOCATE(impl->states, state_hld, 3);

    impl->states[0] = malloc(sizeof(state_type));
    impl->states[1] = malloc(sizeof(state_type));
    impl->states[2] = malloc(sizeof(state_type));

    impl->start = impl->states[0];
    impl->finish = impl->states[1];

    impl->states[0]->mind_profile = NULL;
    MACRO_VECTOR_ALLOCATE(impl->states[0]->steps, state_step_type, 1);

    {
        state_ref state = impl->states[0];
        uint32_t down_data[][2] = {{0, 0}, {1, 1}, {2, 2}};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {};
        uint32_t up_transforms[][2] = {};
        MACRO_STRING_COPY(state->steps[0].transform_profile, "context_filter");
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[2];
    }

    impl->states[2]->mind_profile = NULL;
    MACRO_VECTOR_ALLOCATE(impl->states[2]->steps, state_step_type, 1);

    {
        state_ref state = impl->states[2];
        uint32_t down_data[][2] = {};
        uint32_t down_transforms[][2] = {};
        uint32_t up_data[][2] = {{0, 0}};
        uint32_t up_transforms[][2] = {};
        MACRO_STRING_COPY(state->steps[0].transform_profile, "int32_gen_0");
        state->steps[0].download = MACRO_BUILD_TRANSMITTER(down_data, down_transforms);
        state->steps[0].upload = MACRO_BUILD_TRANSMITTER(up_data, up_transforms);
        state->steps[0].next_state = impl->states[1];
    }

    return build_minded_transform(&impl);
}

void run_discriminant_tests(void **state)
{
    (void) state;

    static const int32_t nums[] = {-1023, -239, -2, -1, 0, 1, 2, 239, 1023, 173741823};

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
                assert_int_equal(output->data_size, 3); // ToDo: must be 1
                int32_t vres = int32_datum_extract(output->data[0]);
                datum_destruct(&(output->data[0]));
                context_destruct(&output);

                assert_int_equal(vres, 0); // ToDo: write proper test
                // assert_int_equal(vres, discriminant_classifier(nums[ia], nums[ib], nums[ic]));
            }

    transform_destruct(&classifier);
    assert_null(classifier);
}

