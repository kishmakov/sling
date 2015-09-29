# Sling
[![Build Status](https://travis-ci.org/kishmakov/sling.svg?branch=master)](https://travis-ci.org/kishmakov/sling)
[![GPL V2 License](https://img.shields.io/badge/license-GPL_V2-blue.svg)](https://github.com/kishmakov/sling/blob/master/LICENSE.txt)

## Code Convention

### Ownership

Each structured type definition **must** be done via ```MACRO_STRUCTURE_DEFINITION``` macro.

This macro constructs a number of typedefs, parametrized by ```type_name```:

```c
struct type_name_type; // type itself

typedef struct type_name_type*       type_name_holder;
// object holder; usage: either member description or local variable

typedef struct type_name_type*       type_name_ref;
// modifing reference; usage: parameter specification only; ownership is not transferred

typedef struct const type_name_type* type_name_cref;
// non-modifing reference; usage: parameter specification only; ownership is not transferred

typedef struct type_name_ptr*        type_name_move;
// ownership transferring reference; usage: parameter specification only
```

All type usages are supposed to stick to these guidelines.