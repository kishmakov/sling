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

transform_hld minded_transform_construct(void* minded_transform_impl);

void minded_transform_register(transform_description_io head);
