#pragma once

#include "include/datum.h"
#include "include/state.h"

#include <memory>
#include <vector>

namespace sling {

typedef std::string ComputationType;

struct Computation
{
    virtual State compute(State&& input);

    virtual const ComputationType& type() const = 0;
};

} // sling