# Code Convention

## Ownership

Each structured type definition **must** be done via ```MACRO_STRUCTURE_DEFINITION``` macro.

This macro constructs a number of typedefs, parametrized by ```type_name```:

```c
struct type_name_type; // type itself

typedef struct type_name_type        type_name_type;
// type short name for malloc usage

typedef struct type_name_type*       type_name_hld;
// object holder;
// usage: either member description or local variable

typedef struct type_name_type*       type_name_ref;
// modifing reference;
// usage: parameter specification only; ownership is not transferred

typedef struct const type_name_type* type_name_cref;
// non-modifing reference;
// usage: parameter specification only; ownership is not transferred

typedef struct type_name_ptr**       type_name_mv;
// ownership transferring reference;
// usage: parameter specification only
```

All type usages are supposed to stick to these guidelines.