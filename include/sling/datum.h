#pragma once

#include <memory>
#include <string>
#include <vector>

namespace sling {

typedef std::vector<char> Bytes;

struct Datum
{
    virtual const Bytes& entity() const = 0;
    virtual const std::string& scheme() const = 0;
};


} // sling