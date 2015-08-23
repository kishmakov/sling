#pragma once

#include "include/junction.h"

#include <memory>
#include <string>
#include <vector>

namespace sling {

struct Datum;
typedef std::unique_ptr<Datum> DatumUPtr;

typedef std::vector<char> Bytes;

struct Mind
{
    virtual Index direct(const Junction& junction) const = 0;
};

} // sling