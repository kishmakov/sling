#pragma once

#include "sling/computation.h"
#include "sling/junction.h"
#include "sling/mind.h"

#include <list>

namespace sling {

struct State;

typedef State* StatePtr;
typedef std::unique_ptr<State> StateUPtr;

struct State
{
    JunctionUPtr junction;
    std::vector<StatePtr> successors;
};

struct MindedComputation : public Computation
{
    virtual DeterminacyUPtr compute(DeterminacyUPtr input);

    MindUPtr mind;
};

} // sling