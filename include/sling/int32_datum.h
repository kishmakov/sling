#pragma once

#include "sling/datum.h"

#include <string.h>

namespace sling {

struct Int32Datum : public Datum
{
    Int32Datum(int32_t value):
        bytes_(sizeof(int32_t))
    {
        memcpy(static_cast<void*>(bytes_.data()), static_cast<void*>(&value), sizeof(int32_t));
    }

    virtual const Bytes& entity() const { return bytes_; }

    virtual const std::string& scheme() const { return scheme_; };

private:
    const std::string scheme_ = "{\"int32\": 1}";
    Bytes bytes_;
};


} // sling