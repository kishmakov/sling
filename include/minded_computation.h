#pragma once

#include "include/computation.h"

#include "include/mind.h"


namespace sling {

struct MindedComputation : public Computation
{
    virtual State compute(State&& input);

    MindUPtr mind;
};

} // sling