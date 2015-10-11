#include "tests_tools.h"

#include "transforms/int32_gen.h"
#include "types/int32.h"

#include <stdlib.h>

const int32_t vs[] = {-1073741823, -1023, 0, 1023, 1073741823};
const uint32_t N = sizeof(vs) / sizeof(int32_t);

int32_t test_get_int(transform_cref int32_gen)
{
    context_hld input = context_construct(0, 0);
    context_hld output = transform_function(int32_gen, &input);
    assert(input == NULL);
    assert(output->data_size == 1);
    assert(output->transforms_size == 0);

    int32_t result = int32_datum_extract(output->data[0]);
    datum_destruct(&(output->data[0]));
    context_destruct(&output);

    return result;
}