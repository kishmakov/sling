#pragma once

#include "sling/computation.h"
#include "sling/int32_datum.h"

#include <assert.h>
#include <memory>

namespace sling {

struct Int32Sum : public Computation
{
    virtual ContextUPtr compute(ContextUPtr input)
    {
        assert(input->data.size() == 2);

        const auto& data0 = input->data[0]->entity();
        const auto& data1 = input->data[1]->entity();
        int32_t value0;
        memcpy(static_cast<void*>(&value0), static_cast<const void*>(data0.data()), sizeof(int32_t));
        int32_t value1;
        memcpy(static_cast<void*>(&value1), static_cast<const void*>(data1.data()), sizeof(int32_t));

        ContextUPtr result(new Context);
        result->data.resize(1);
        result->data[1].reset(new Int32Datum(value0 + value1));

        return result;
    }

    virtual const ComputationType& type() const { return type_; }

private:
    ComputationType type_ = "sum";
};

} // sling