#pragma once

#ifndef NDEBUG
#define DEBUG_MODE 1
#define DEBUG(argument) argument
#define DLOG(...) LOG( __VA_ARGS__)
#else
#define DEBUG_MODE 0
#define DEBUG(argument)
#define DLOG(...)
#endif

#include <assert.h>

#include "utils/allocation_list.h"
