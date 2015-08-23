#pragma once

#include "sling/computation.h"
#include "sling/determinacy.h"

namespace sling {

struct Junction
{
    struct Direction {
        ComputationType type;
        TransmitterUPtr transmitter;
    };

    Determinacy determinacy;

    std::vector<Direction> directions;
};

typedef std::unique_ptr<Junction> JunctionUPtr;

} // sling