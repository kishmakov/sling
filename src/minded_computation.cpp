#include "sling/computation.h"

namespace sling {

State Computation::compute(State&& input)
{
    return std::move(input);
}

} // sling
