#pragma once

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "common/result.h"

void vlog_errno(const char *fmt, va_list args);

Result log_init(const char *path);

void log_close(void);

void log_info(const char *fmt, ...);

void log_warn(const char *fmt, ...);

void log_error(const char *fmt, ...);

void log_errno(const char *fmt, ...);

