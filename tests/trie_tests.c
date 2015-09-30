#include "trie_tests.h"

#include "unit_tests_main.h"

#include "utils/trie.h"

static void trie_test_1(void)
{
    char* strings[] = {"abacaba", "aba", "abba", "baba"};
    int v[] = {1, 2, 3, 4};

    void * out_holder = NULL;
    trie_hld test_trie = NULL;

    for (int i = 0; i < 4; i++)
        trie_insert(&test_trie, strings[i], &v[i]);

    for (int i = 0; i < 4; i++)
        assert_ptr_equal(&v[i], trie_check(test_trie, strings[i]));

    test_trie = trie_remove(&test_trie, strings[0], &out_holder);
    assert_ptr_equal(&v[0], out_holder);
    test_trie = trie_remove(&test_trie, strings[0], &out_holder);
    assert_null(out_holder);

    test_trie = trie_remove(&test_trie, strings[3], &out_holder);
    assert_ptr_equal(&v[3], out_holder);
    test_trie = trie_remove(&test_trie, strings[3], &out_holder);
    assert_null(out_holder);

    void* vv[] = {NULL, &v[1], &v[2], NULL};

    for (int i = 0; i < 4; i++)
        assert_ptr_equal(vv[i], trie_check(test_trie, strings[i]));

    test_trie = trie_remove(&test_trie, strings[1], &out_holder);
    assert_ptr_equal(&v[1], out_holder);
    test_trie = trie_remove(&test_trie, strings[1], &out_holder);
    assert_null(out_holder);

    test_trie = trie_remove(&test_trie, strings[2], &out_holder);
    assert_ptr_equal(&v[2], out_holder);
    test_trie = trie_remove(&test_trie, strings[2], &out_holder);
    assert_null(out_holder);
}

static void trie_test_2(void)
{
    void * out_holder = NULL;
    trie_hld test_trie = NULL;

    const char* strings[] = {
        "a",
        "aa",
        "aaa",
        "aabb",
        "ab",
        "aba",
        "abab",
        "ababa",
        "abaca",
        "abacab",
        "abacaba",
        "abba",
        "abbc",
        "abc",
        "abcabc",
        "abccba",
        "b",
        "ba",
        "bab",
        "baba",
        "babca",
        "bb",
        "bbb",
        "bcb",
        "c",
        "cc",
        "ccc",
    };

    const int NUM = sizeof(strings) / sizeof(char*);

    int v[NUM];
    int count[NUM];

    memset(v, 0, sizeof(v));
    memset(count, 0, sizeof(count));

    for (int i = 0; i < 10000; i++) {
        int action = i % 3;

        const char* string = strings[i % NUM];
        void* ptr = count[i % NUM] == 0 ? NULL : &v[i % NUM];

        if (action == 0) { // check
            assert_ptr_equal(trie_check(test_trie, string), ptr);
        } else if (action == 1 && count[i % NUM] == 0) { // add
            count[i % NUM] = 1;
            trie_insert(&test_trie, string, &v[i % NUM]);
        } else {
            count[i % NUM] = 0;
            test_trie = trie_remove(&test_trie, string, &out_holder);
            assert_ptr_equal(out_holder, ptr);
        }
    }

    for (int i = 0; i < NUM; i++) {
        const char* string = strings[i];
        test_trie = trie_remove(&test_trie, string, &out_holder);
        assert_ptr_equal(out_holder, count[i] == 0 ? NULL : &v[i]);
    }
}

void run_trie_tests(void **state)
{
    (void) state;

    trie_test_1();
    trie_test_2();
}
