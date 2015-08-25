#pragma once

#include "sling/computation.h"
#include "sling/mind.h"
#include "sling/symbol.h"

#include <list>

namespace sling {

struct State;

typedef State* StatePtr;
typedef std::unique_ptr<State> StateUPtr;

struct State
{
    SymbolUPtr symbol;
    std::vector<StatePtr> successors;
};

struct MindedComputation : public Computation
{
    virtual ContextUPtr compute(ContextUPtr input);

    MindUPtr mind;
};

} // sling