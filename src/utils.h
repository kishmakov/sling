#pragma once

#define MACRO_MIN(x, y)  ((x) < (y) ? (x) : (y))

#define MACRO_STRUCTURE_DEFINITION(type_name) \
struct type_name ## _type; \
typedef struct type_name ## _type type_name ## _type; \
typedef type_name ## _type* type_name ## _ptr; \
struct type_name ## _type