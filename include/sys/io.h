#pragma once

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

int husk_pipe(int pipefd[2]);

ssize_t husk_read(int fd, void *buf, size_t count);

ssize_t husk_write(int fd, const void *buf, size_t count);

int husk_open(const char *path, int flags, mode_t mode);

int husk_close(int fd);

