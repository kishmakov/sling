#pragma once

#define MACRO_MIN(x, y)  ((x) < (y) ? (x) : (y))

#define MACRO_STRUCTURE_DEFINITION(type_name) \
struct type_name ## _type; \
typedef struct type_name ## _type type_name ## _type; \
typedef type_name ## _type* type_name ## _ptr; \
typedef const type_name ## _type* type_name ## _cptr; \
struct type_name ## _type

#define MACRO_VECTOR_DEFINITION(name, type_name) \
uint32_t name ## _size; \
type_name* name

#define MACRO_TRANSFORM_INITIALIZER(type_name) \
type_name ## _description = malloc(sizeof(transform_description_type)); \
type_name ## _description->input_scheme = type_name ## _input; \
type_name ## _description->output_scheme = type_name ## _output; \
type_name ## _description->profile = type_name ## _profile; \
type_name ## _description->construct = &type_name ## _construct; \
type_name ## _description->destruct = &type_name ## _destruct; \
type_name ## _description->function = &type_name ## _function

#define MACRO_VECTOR_ALLOCATE(name, type_name, requested_size) \
name ## _size = requested_size; \
name = requested_size > 0 ? malloc(sizeof(type_name) * requested_size) : NULL

#define MACRO_STRINGIFY(value) #value
#define MACRO_QUOTE(value) MACRO_STRINGIFY(value)

char* scheme_description(const char * data, const char * transforms);