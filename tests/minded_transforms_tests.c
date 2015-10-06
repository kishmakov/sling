#include "minded_transforms_tests.h"

#include "tests_tools.h"
#include "unit_tests_main.h"

#include "minds/int32_sign.h"
#include "mt/minded_transform.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_gen.h"
#include "transforms/int32_mult_by.h"
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
    MACRO_VECTOR_ALLOCATE(impl->states, state_hld, 10);

    trie_insert(&(impl->minds), "int32_sign", int32_sign_construct());
    trie_insert(&(impl->transforms), "int32_dupl", build_int32_duplicator());


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
                assert_int_equal(output->data_size, 1);
                int32_t vres = int32_datum_extract(output->data[0]);
                datum_destruct(&(output->data[0]));
                context_destruct(&output);

                assert_int_equal(vres, discriminant_classifier(nums[ia], nums[ib], nums[ic]));
            }

    transform_destruct(&classifier);
    assert_null(classifier);
}

