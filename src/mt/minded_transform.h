#pragma once

#include "mt/state.h"
#include "utils/list.h"
#include "utils/trie.h"
#include "utils/utils.h"

MACRO_STRUCTURE_DEFINITION(minded_transform_impl) {
    MACRO_VECTOR_DEFINITION(states, state_hld);

    state_cref start;
    state_cref finish;

    trie_hld minds;
    trie_hld transforms;
};

transform_hld build_minded_transform(minded_transform_impl_mv impl);

void minded_transform_register(transform_description_io head);
