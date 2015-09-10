#include "trie_tests.h"

#include "unit_tests_main.h"

#include "utils/trie.h"

void run_trie_tests(void **state)
{
    (void) state;

    char* s[] = {"abacaba", "aba", "abba", "baba"};
    int v[] = {1, 2, 3, 4};

    trie test_trie = NULL;

    for (int i = 0; i < 4; i++)
        trie_insert(&test_trie, s[i], &v[i]);

    for (int i = 0; i < 4; i++)
        assert_ptr_equal(&v[i], trie_check(&test_trie, s[i]));

    assert_ptr_equal(&v[0], trie_remove(&test_trie, s[0]));
    assert_null(trie_remove(&test_trie, s[0]));
    assert_ptr_equal(&v[3], trie_remove(&test_trie, s[3]));
    assert_null(trie_remove(&test_trie, s[3]));

    void* vv[] = {NULL, &v[1], &v[2], NULL};

    for (int i = 0; i < 4; i++)
        assert_ptr_equal(vv[i], trie_check(&test_trie, s[i]));

    assert_ptr_equal(&v[1], trie_remove(&test_trie, s[1]));
    assert_null(trie_remove(&test_trie, s[1]));
    assert_ptr_equal(&v[2], trie_remove(&test_trie, s[2]));
    assert_null(trie_remove(&test_trie, s[2]));
}
