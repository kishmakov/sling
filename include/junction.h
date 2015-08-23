#pragma once

#include "include/computation.h"
#include "include/state.h"

namespace sling {

struct Junction
{
    struct Direction {
        ComputationType type;
        Transmitter transmitter;
    };

    State state;

    std::vector<Direction> directions;
};

} // sling