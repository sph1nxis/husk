#include "sys/fs.h"

#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

int husk_mount(
    const char *source,
    const char *target,
    const char *filesystemtype,
    unsigned long flags,
    const void *data
) {
    return mount(source, target, filesystemtype, flags, data);
}

int husk_chroot(const char *path) {
    return chroot(path);
}

int husk_chdir(const char *path) {
    return chdir(path);
}

int husk_mkdir(const char *path, mode_t mode) {
    return mkdir(path, mode);
}

int husk_stat(const char *path, struct stat *st) {
    return stat(path, st);
}

