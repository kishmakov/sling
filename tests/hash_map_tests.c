#include "hash_map_tests.h"

#include "unit_tests_main.h"

#include "utils/hash_map.h"

void run_hash_map_tests(void **state)
{
    (void) state;

    const uint32_t COUNT_NUM = 10007;

    int count[COUNT_NUM];
    memset(count, 0, sizeof(count));

    hm_hld map = hm_uint32_uint32_construct(0);

    for (uint32_t i = 0; i < 100000; i++) {
        uint32_t action = i % 3;
        uint32_t key = i % COUNT_NUM;

        uint32_t need = count[key] == 0 ? HM_UINT32_UINT32_NIL : key;

        if (action == 0) { // check
            uint32_t have = hm_uint32_uint32_lookup(map, key);
            assert_int_equal(have, need);
        } else if (action == 1 && count[key] == 0) { // add
            count[key] = 1;
            hm_uint32_uint32_insert(map, key, key);
        } else {
            count[key] = 0;
            uint32_t have = hm_uint32_uint32_remove(map, key);
            assert_int_equal(have, need);
        }
    }

    hm_destruct(&map);
    assert_null(map);
}
