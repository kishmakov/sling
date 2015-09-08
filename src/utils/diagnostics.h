#pragma once

#ifndef NDEBUG
#define DEBUG_MODE 1
#define DEBUG(argument) argument
#else
#define DEBUG_MODE 0
#define DEBUG(argument)
#endif

#include <assert.h>

#include "utils/allocation_list.h"
