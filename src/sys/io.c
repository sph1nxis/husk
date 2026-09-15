#include "sys/io.h"

#include <unistd.h>

int husk_pipe(int pipefd[2]) {
    return pipe(pipefd);
}

ssize_t husk_read(int fd, void *buf, size_t count) {
    return read(fd, buf, count);
}

ssize_t husk_write(int fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}

int husk_open(const char *path, int flags, mode_t mode) {
    return open(path, flags, mode);
}

int husk_close(int fd) {
    return close(fd);
}

