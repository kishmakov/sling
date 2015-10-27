#include "unit_tests_main.h"

#include "basic_minds_tests.h"
#include "basic_transforms_tests.h"
#include "context_filter_tests.h"
#include "hash_map_tests.h"
#include "minded_transforms_tests.h"
#include "transmitter_tests.h"
#include "trie_tests.h"

#include "sling_init.h"

int main(int argc, char ** argv)
{
    sling_init(argc >= 2 ? argv[1] : NULL);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(run_transmitter_tests),
        cmocka_unit_test(run_hash_map_tests),
        cmocka_unit_test(run_trie_tests),

        // basic_transforms_tests
        cmocka_unit_test(run_context_filter_tests),
        cmocka_unit_test(run_int32_addition_tests),
        cmocka_unit_test(run_int32_duplicator_tests),
        cmocka_unit_test(run_int32_gen_tests),
        cmocka_unit_test(run_int32_mult_by_tests),
        cmocka_unit_test(run_int32_multiplication_tests),
        cmocka_unit_test(run_int32_to_double_tests),

        // basic_minds_tests
        cmocka_unit_test(run_int32_compare_tests),
        cmocka_unit_test(run_int32_sign_tests),

        // minded_transforms_tests
        cmocka_unit_test(run_discriminant_tests),
    };

    int rv = cmocka_run_group_tests(tests, NULL, NULL);

    sling_fini();

    return rv;
}
