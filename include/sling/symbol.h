#pragma once

#include "sling/computation.h"
#include "sling/context.h"

namespace sling {

struct Symbol
{
    struct Direction {
        ComputationType type;
        TransmitterUPtr transmitter;
    };

    Context context;

    std::vector<Direction> directions;
};

typedef std::unique_ptr<Symbol> SymbolUPtr;

} // sling