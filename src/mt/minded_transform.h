#pragma once

#include "mt/state.h"
#include "utils/lists.h"
#include "utils/trie.h"
#include "utils/utils.h"

MACRO_STRUCTURE_DEFINITION(minded_transform) {
    list states;
    trie minds;
    trie transforms;
};
