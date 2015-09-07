#pragma once

#ifndef NDEBUG
#define DIAG_MODE 1
#define DIAG(argument) argument
#else
#define DIAG_MODE 0
#define DIAG(argument)
#endif

#include <assert.h>

#include "utils/allocation_list.h"
