#pragma once

#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MACRO_MIN(x, y)  ((x) < (y) ? (x) : (y))
#define MACRO_MAX(x, y)  ((x) > (y) ? (x) : (y))

typedef void**      void_mv;
typedef void*       void_hld;
typedef const void* void_cref;
typedef void*       void_ref;

typedef char**      char_mv;
typedef char*       char_hld;
typedef const char* char_cref;
typedef char*       char_ref;

#define MACRO_STRUCTURE_DEFINITION(type_name) \
struct type_name ## _type; \
typedef struct type_name ## _type        type_name ## _type; \
typedef struct type_name ## _type*       type_name ## _hld; \
typedef struct type_name ## _type*       type_name ## _ref; \
typedef const struct type_name ## _type* type_name ## _cref; \
typedef struct type_name ## _type**      type_name ## _mv; \
typedef struct type_name ## _type**      type_name ## _io; \
struct type_name ## _type

#define MACRO_TRANSFORM_INITIALIZER(type_name) \
type_name ## _description = malloc(sizeof(transform_description_type)); \
type_name ## _description->input_scheme = &type_name ## _input_scheme; \
type_name ## _description->output_scheme = &type_name ## _output_scheme; \
type_name ## _description->profile = &type_name ## _profile; \
type_name ## _description->construct = &type_name ## _construct; \
type_name ## _description->copy = &type_name ## _copy; \
type_name ## _description->destruct = &type_name ## _destruct; \
type_name ## _description->function = &type_name ## _function

#define MACRO_MIND_INITIALIZER(type_name) \
type_name ## _description = malloc(sizeof(mind_description_type)); \
type_name ## _description->input_scheme = type_name ## _input; \
type_name ## _description->decision_scheme = type_name ## _decision; \
type_name ## _description->profile = type_name ## _profile; \
type_name ## _description->construct = &type_name ## _construct; \
type_name ## _description->destruct = &type_name ## _destruct; \
type_name ## _description->function = &type_name ## _function

#define MACRO_VECTOR_DEFINITION(name, type_name) \
uint32_t name ## _size; \
type_name* name

#define MACRO_VECTOR_ALLOCATE(name, type_name, requested_size) \
name ## _size = requested_size; \
name = requested_size > 0 ? malloc(sizeof(type_name) * requested_size) : NULL; \
if (requested_size > 0) \
    memset(name, 0, sizeof(type_name) * requested_size)

#define MACRO_VECTOR_RESIZE(name, type_name, new_size) \
if (name ## _size < (new_size)) { \
    name = realloc(name, sizeof(type_name) * (new_size)); \
    memset(name + name ## _size, 0, sizeof(type_name) * (new_size - name ## _size)); \
    name ## _size = new_size; \
}

#define MACRO_STRING_COPY(dst, src) \
dst = malloc(strlen(src) + 1); \
strcpy((char*) dst, src)

#define MACRO_STRINGIFY(value) #value
#define MACRO_QUOTE(value) MACRO_STRINGIFY(value)

char* context_scheme(const char* data, const char* transforms);
char* decision_scheme(const char* alternatives[], const uint32_t alternatives_number);

// correspondence between objects and pointers to its representation

static inline void_hld double_to_ptr(double val)
{
    void_hld result = malloc(sizeof(double));
    memcpy(result, (void*) &val, sizeof(double));
    return result;
}

static inline double ptr_to_double(void_cref ptr)
{
    double result;
    memcpy((void*) &result, ptr, sizeof(double));
    return result;
}

static inline void_hld int32_to_ptr(int32_t val)
{
    void_hld result = malloc(sizeof(int32_t));
    memcpy(result, (void*) &val, sizeof(int32_t));
    return result;
}

static inline int32_t ptr_to_int32(void_cref ptr)
{
    int32_t result;
    memcpy((void*) &result, ptr, sizeof(int32_t));
    return result;
}

static inline void_hld uint32_to_ptr(uint32_t val)
{
    void_hld result = malloc(sizeof(uint32_t));
    memcpy(result, (void*) &val, sizeof(uint32_t));
    return result;
}

static inline uint32_t ptr_to_uint32(void_cref ptr)
{
    uint32_t result;
    memcpy((void*) &result, ptr, sizeof(uint32_t));
    return result;
}

static inline void_mv void_r2m(void_ref value)
{
    void_mv value_ptr = malloc(sizeof(void_hld));
    memcpy(value_ptr, (void*) &value, sizeof(void_hld));
    return value_ptr;
}
