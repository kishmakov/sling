#pragma once

#include "sling/computation.h"
#include "sling/state.h"

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