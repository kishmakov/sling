#pragma once

#include "sling/symbol.h"

#include <memory>
#include <string>
#include <vector>

namespace sling {

typedef std::vector<char> Bytes;

struct Mind
{
    virtual Index direct(const Symbol& symbol) const = 0;
};

typedef std::unique_ptr<Mind> MindUPtr;

} // sling