# Code Conventions

## Ownership

Each structured type definition **must** be done via ```MACRO_STRUCTURE_DEFINITION``` macro.

This macro constructs a number of typedefs, parametrized by ```type_name```:

```c
struct type_name_type; // type itself

typedef struct type_name_type        type_name_type;
// type short name for malloc usage

typedef struct type_name_type*       type_name_hld;
// object owning holder
// usage: member description or local variable or return value

typedef struct type_name_type*       type_name_ref;
// non-owning modifing reference
// usage: parameter specification or return value

typedef struct const type_name_type* type_name_cref;
// non-owning constant reference
// usage: parameter specification or return value

typedef struct type_name_ptr**       type_name_mv;
// object owning holder
// usage: parameter specification only

typedef struct type_name_ptr**       type_name_io;
// in-out object owning holder which would be modified after usage
// usage: parameter specification only
// it is designed to shorten constructions of the form:
//     some_hld a;
//     ...
//     a = function(&a, ...);
```

All type usages are supposed to stick to these guidelines.

## Transforms

Each transform element has a pointer to its description of type ```transform_description_type```.

Descriptional element contains next functions (see [the source code]
(https://github.com/kishmakov/sling/blob/master/src/transforms/transform_description.h) for full
description)


```c
transform_hld (*construct)(void_mv internal_data);
// constructor like function; it is supposed to accept ownership of provided
// auxiliary internal_data and nullify pointer upon completion

transform_hld (*copy)(transform_cref transform);
// copy-constructor like function; it must take care about proper copying of
// internal data

void (*destruct)(transform_mv transform);
// TODO: annotate me

context_hld (*function)(transform_cref transform, context_mv input);
// TODO: annotate me
```
