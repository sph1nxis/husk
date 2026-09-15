#pragma once

#include <fcntl.h>

int husk_mount(
    const char *source,
    const char *target,
    const char *filesystemtype,
    unsigned long flags,
    const void *data
);

int husk_chroot(const char *path);

int husk_chdir(const char *path);

int husk_mkdir(const char *path, mode_t mode);

int husk_stat(const char *path, struct stat *st);

