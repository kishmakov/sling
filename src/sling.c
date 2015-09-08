#include "context.h"
#include "init.h"
#include "transforms/int32_addition.h"
#include "transforms/int32_duplicator.h"
#include "transforms/int32_to_double.h"
#include "types/int32.h"
#include "types/double.h"

#include <assert.h>
#include <stdio.h>
#include <memory.h>

void test1()
{
    int32_t v0 = 1023;
    int32_t v1 = 10000;

    context_ptr input = context_create(2, 0);
    input->data[0] = int32_datum_create(v0);
    input->data[1] = int32_datum_create(v1);

    transform_ptr addition = int32_addition_create();

    printf("t1: input: %s\n", addition->description->input_scheme);
    printf("t1: output: %s\n", addition->description->output_scheme);
    printf("t1: profile: %s\n", addition->description->profile);

    context_ptr output = int32_addition_func(addition, &input);

    assert(input == NULL);
    assert(output->data_size == 1);

    int32_t vres = int32_datum_extract(output->data[0]);
    datum_delete(&(output->data[0]));
    context_delete(&output);

    printf("%d = %d + %d =?= %d\n", v0 + v1, v0, v1, vres);
}

void test2()
{
    int32_t v = 239;

    context_ptr input = context_create(1, 0);
    input->data[0] = int32_datum_create(v);

    transform_ptr duplicator = int32_duplicator_create();

    printf("t2: input: %s\n", duplicator->description->input_scheme);
    printf("t2: output: %s\n", duplicator->description->output_scheme);
    printf("t2: profile: %s\n", duplicator->description->profile);

    context_ptr output = int32_duplicator_func(duplicator, &input);

    assert(input == NULL);
    assert(output->data_size == 2);

    int32_t v1 = int32_datum_extract(output->data[0]);
    int32_t v2 = int32_datum_extract(output->data[1]);
    datum_delete(&(output->data[0]));
    datum_delete(&(output->data[1]));
    context_delete(&output);

    printf("%d -> {%d, %d}\n", v, v1, v2);
}

void test3()
{
    int32_t vi = 239;

    context_ptr input = context_create(1, 0);
    input->data[0] = int32_datum_create(vi);

    transform_ptr converter = int32_to_double_create();

    printf("t3: input: %s\n", converter->description->input_scheme);
    printf("t3: output: %s\n", converter->description->output_scheme);
    printf("t3: profile: %s\n", converter->description->profile);

    context_ptr output = int32_to_double_func(converter, &input);

    assert(input == NULL);
    assert(output->data_size == 1);

    double vd = double_datum_extract(output->data[0]);
    datum_delete(&(output->data[0]));
    context_delete(&output);

    printf("%d -> %f\n", vi, vd);
}


int main(int argc, char ** argv)
{
    const char * log_file_name = NULL;

    if (argc == 2)
        log_file_name = argv[1];

    init(log_file_name);

    test1();
    test2();
    test3();

    fini();

    return 0;
}