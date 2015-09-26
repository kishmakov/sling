# Sling
[![Build Status](https://travis-ci.org/kishmakov/sling.svg?branch=master)](https://travis-ci.org/kishmakov/sling)
[![GPL V2 License](https://img.shields.io/badge/license-GPL_V2-blue.svg)](https://github.com/kishmakov/sling/blob/master/LICENSE.txt)

## Code Convention

Each structured type definition **must** be done with ```MACRO_STRUCTURE_DEFINITION``` macro.

This macro constructs a number of typedefs, parametrized by ```type_name```:

```c
struct type_name_type;
typedef struct type_name_type type_name_type; // short name
typedef type_name_type* type_name_ptr; // modifying non-holding pointer
typedef const type_name_type* type_name _cptr; // constant pointer acting as reference
typedef type_name_ptr* type_name_holder; // actual holder of the object
```
