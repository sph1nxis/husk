#include "utils/log.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "sys/sys.h"

enum {
    kLogBufferSize = 4096
};

static int log_fd = STDERR_FILENO;

static void log_message(
    const char *level,
    const char *fmt,
    va_list args
) {
    char buffer[kLogBufferSize];
    int offset = 0;

    pid_t pid = sys_getpid();

    time_t now = time(NULL);
    struct tm tm_now;

    localtime_r(&now, &tm_now);

    offset += snprintf(
        buffer + offset,
        sizeof(buffer) - offset,
        "%04d-%02d-%02d %02d:%02d:%02d [%s] [pid=%d] ",
        tm_now.tm_year + 1900,
        tm_now.tm_mon + 1,
        tm_now.tm_mday,
        tm_now.tm_hour,
        tm_now.tm_min,
        tm_now.tm_sec,
        level,
        pid
    );

    if (offset < 0 || offset >= (int) sizeof(buffer)) {
        return;
    }

    offset += vsnprintf(buffer + offset, sizeof(buffer) - offset, fmt, args);

    if (offset < 0 || offset >= (int) sizeof(buffer)) {
        return;
    }

    buffer[offset] = '\n';
    ++offset;

    if (offset > (int) sizeof(buffer)) {
        offset = sizeof(buffer);
    }

    sys_write(log_fd, buffer, offset);
}

Result log_init(const char *path) {
    int fd = sys_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        return result_errno_to_result();
    }

    log_fd = fd;

    return kResultOk;
}

void log_close(void) {
    if (log_fd != STDERR_FILENO) {
        sys_close(log_fd);
    }
}

void log_info(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    log_message("INFO", fmt, args);
    va_end(args);
}

void log_warn(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    log_message("WARN", fmt, args);
    va_end(args);
}

void log_error(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    log_message("ERROR", fmt, args);
    va_end(args);
}

void log_errno(const char *fmt, ...) {
    int saved_errno = errno;

    char user_msg[kLogBufferSize];

    va_list args;
    va_start(args, fmt);

    vsnprintf(user_msg, sizeof(user_msg), fmt, args);

    va_end(args);

    char buffer[kLogBufferSize];
    int offset = 0;

    pid_t pid = sys_getpid();

    time_t now = time(NULL);
    struct tm tm_now;

    localtime_r(&now, &tm_now);

    offset += snprintf(
        buffer + offset,
        sizeof(buffer) - offset,
        "%04d-%02d-%02d %02d:%02d:%02d [ERROR] [pid=%d] %s: %s\n",
        tm_now.tm_year + 1900,
        tm_now.tm_mon + 1,
        tm_now.tm_mday,
        tm_now.tm_hour,
        tm_now.tm_min,
        tm_now.tm_sec,
        pid,
        user_msg,
        strerror(saved_errno)
    );

    if (offset > 0) {
        sys_write(log_fd, buffer, offset);
    }
}

