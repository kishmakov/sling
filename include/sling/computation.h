#pragma once

#include "sling/datum.h"
#include "sling/state.h"

#include <memory>
#include <vector>

namespace sling {

typedef std::string ComputationType;

struct Computation
{
    virtual State compute(State&& input) = 0;

    virtual const ComputationType& type() const = 0;
};

} // sling