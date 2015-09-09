#pragma once

#include "sling/context.h"
#include "sling/types/datum.h"

#include <memory>
#include <vector>

namespace sling {

typedef std::string ComputationType;

struct Computation
{
    virtual ContextUPtr compute(ContextUPtr input) = 0;

    virtual const ComputationType& type() const = 0;
};

} // sling