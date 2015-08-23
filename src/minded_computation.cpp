#include "sling/minded_computation.h"

namespace sling {

DeterminacyUPtr MindedComputation::compute(DeterminacyUPtr input)
{
    return std::move(input);
}

} // sling
