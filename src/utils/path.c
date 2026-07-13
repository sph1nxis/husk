#include "utils/path.h"

#include <stdarg.h>
#include <stdio.h>

#include "utils/log.h"

int path_join(char *buffer, size_t size, const char *left, const char *right) {
    while (*right == '/') {
        ++right;
    }

    return path_printf(buffer, size, "%s/%s", left, right);
}

int path_printf(char *buffer, size_t size, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    int len = vsnprintf(buffer, size, fmt, args);

    va_end(args);

    if (len < 0 || (size_t) len >= size) {
        log_error("path is too long");
        return -1;
    }

    return 0;
}
