#pragma once

#include "sling/computation.h"
#include "sling/context.h"

namespace sling {


struct Symbol
{
    struct Direction
    {
        ComputationType type;
        TransmitterUPtr selection;
    };

    typedef Direction* DirectionPtr;
    typedef std::unique_ptr<Direction> DirectionUPtr;

    std::vector<DirectionUPtr> directions;
};

typedef Symbol* SymbolPtr;
typedef std::unique_ptr<Symbol> SymbolUPtr;

} // sling