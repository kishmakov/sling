#include "sling/int32_sum.h"

#include <iostream>

int main(int argc, char ** argv)
{
    sling::ContextUPtr input;
    input->data.emplace_back(new sling::Int32Datum(5));
    input->data.emplace_back(new sling::Int32Datum(8));

    sling::Int32Sum sum;

    auto output = sum.compute(std::move(input));

    const auto& entity = output->data[0]->entity();

    int32_t value;
    memcpy(static_cast<void*>(&value), static_cast<const void*>(entity.data()), sizeof(int32_t));

    std::cout << "5 + 8 = " << value << std::endl;

    return 0;
}