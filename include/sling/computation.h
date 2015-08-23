#pragma once

#include "sling/datum.h"
#include "sling/determinacy.h"

#include <memory>
#include <vector>

namespace sling {

typedef std::string ComputationType;

struct Computation
{
    virtual DeterminacyUPtr compute(DeterminacyUPtr input) = 0;

    virtual const ComputationType& type() const = 0;
};

} // sling