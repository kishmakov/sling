#pragma once

#include "mt/state.h"
#include "utils/list.h"
#include "utils/trie.h"
#include "utils/utils.h"

MACRO_STRUCTURE_DEFINITION(minded_transform_impl) {
    list_mv states;

    state_cref start;
    state_cref finish;

    trie_hld minds;
    trie_hld transforms;
};
