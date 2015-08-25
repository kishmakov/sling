#pragma once

#include "sling/symbol.h"

#include <memory>
#include <string>
#include <vector>

namespace sling {

typedef std::vector<char> Bytes;

struct Mind
{
    virtual Symbol::DirectionPtr direct(const SymbolPtr symbol, const ContextPtr context) const = 0;
};

typedef std::unique_ptr<Mind> MindUPtr;

} // sling