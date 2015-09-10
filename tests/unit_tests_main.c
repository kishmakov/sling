#include "unit_tests_main.h"

#include "basic_transforms_tests.h"
#include "trie_tests.h"

#include "sling_init.h"

int main(int argc, char ** argv)
{
    const char * log_file_name = NULL;

    sling_init(argc >= 2 ? argv[1] : NULL);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(run_trie_tests),
        cmocka_unit_test(run_int32_addition_tests),
        cmocka_unit_test(run_int32_duplicator_tests),
        cmocka_unit_test(run_int32_to_double_tests),
    };

    int rv = cmocka_run_group_tests(tests, NULL, NULL);

    sling_fini();

    return rv;
}