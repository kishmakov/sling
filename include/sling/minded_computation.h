#pragma once

#include "sling/computation.h"
#include "sling/mind.h"
#include "sling/symbol.h"

#include <unordered_map>

namespace sling {

struct State;

typedef State* StatePtr;
typedef std::unique_ptr<State> StateUPtr;

struct State
{
    TransmitterUPtr download; // maps global to symbol context
    TransmitterUPtr upload; // maps symbol context back to global

    SymbolUPtr symbol;

    struct Successor
    {
        StatePtr state;
        TransmitterUPtr upload;
    };
    typedef std::unique_ptr<Successor> SuccessorUPtr;

    std::unordered_map<ComputationType, SuccessorUPtr> successors;
};

struct MindedComputation : public Computation
{
    virtual ContextUPtr compute(ContextUPtr input);

    TransmitterUPtr initialization; // maps input to global context
    TransmitterUPtr finalization; // maps global to result context

    StatePtr initialState;
    std::vector<StateUPtr> states;

    MindUPtr mind;

    ContextUPtr globalContext; // holds computation "data" along execution

    std::unordered_map<ComputationType, ComputationUPtr> substeps;
};

} // sling