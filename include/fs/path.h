#pragma once

#include <stddef.h>

#include "common/result.h"

Result path_join(char *buffer, size_t size, const char *left, const char *right);

Result path_printf(char *buffer, size_t size, const char *fmt, ...);

