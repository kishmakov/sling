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

#define MACRO_VECTOR_ALLOCATE(name, type_name, requested_size) \
name ## _size = requested_size; \
name = requested_size > 0 ? malloc(sizeof(type_name) * requested_size) : NULL

#define MACRO_STRINGIFY(value) #value
#define MACRO_QUOTE(value) MACRO_STRINGIFY(value)

char* scheme_description(const char * data, const char * transforms);