#include "sling/minded_computation.h"

#include <assert.h>

namespace sling {

ContextUPtr MindedComputation::compute(ContextUPtr inputContext)
{
    assert(initialization != nullptr && finalization != nullptr);

    globalContext.reset(new Context);
    initialization->transmit_move(inputContext.get(), globalContext.get());

    for (StatePtr currentState = initialState; currentState != nullptr; ) {
        // determination of the next step

        ContextUPtr currentContext(new Context);
        currentState->download->transmit_move(globalContext.get(), currentContext.get());
        auto direction = mind->direct(currentState->symbol.get(), currentContext.get());

        // execution of the next step

        ContextUPtr substepInput(new Context);
        //selection of specific data for substep
        direction->selection->transmit_move(currentContext.get(), substepInput.get());
        // restitution of unused data
        currentState->upload->transmit_move(currentContext.get(), globalContext.get());
        auto substep = substeps[direction->type].get();
        assert(substep != nullptr);

        ContextUPtr substepOutput = substep->compute(std::move(substepInput));
        auto successor = currentState->successors[direction->type].get();
        assert(successor != nullptr);

        successor->upload->transmit_move(substepOutput.get(), globalContext.get());
        currentState = successor->state;
    }

    ContextUPtr resultContext(new Context);
    finalization->transmit_move(globalContext.get(), resultContext.get());
    return std::move(resultContext);
}

} // sling
