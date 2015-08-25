#include "sling/minded_computation.h"

namespace sling {

ContextUPtr MindedComputation::compute(ContextUPtr input)
{
    return std::move(input);
}

} // sling
