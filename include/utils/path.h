#pragma once

#include <stddef.h>

int path_join(char *buffer, size_t size, const char *left, const char *right);

int path_printf(char *buffer, size_t size, const char *fmt, ...);

