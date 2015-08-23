#pragma once

#include "sling/computation.h"

#include "sling/mind.h"


namespace sling {

struct MindedComputation : public Computation
{
    virtual State compute(State&& input);

    MindUPtr mind;
};

} // sling