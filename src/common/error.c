#include "common/error.h"

#include <stdarg.h>
#include <stdio.h>

#include "log/log.h"

Result system_error(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vlog_errno(fmt, args);
    va_end(args);

    return result_errno_to_result();
}

