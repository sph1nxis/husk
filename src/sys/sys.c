#define _GNU_SOURCE

// Will use custom ASM implementations later

#include "sys/sys.h"

#include <fcntl.h>
#include <sched.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t husk_clone(int (*fn)(void *), void *stack, int flags, void *arg) {
    return clone(fn, stack, flags, arg);
}

int husk_pipe(int pipefd[2]) {
    return pipe(pipefd);
}

ssize_t husk_read(int fd, void *buf, size_t count) {
    return read(fd, buf, count);
}

ssize_t husk_write(int fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}

pid_t husk_waitpid(pid_t pid, int *status, int options) {
    return waitpid(pid, status, options);
}

int husk_execvp(const char *file, char *const argv[]) {
    return execvp(file, argv);
}

int husk_sethostname(const char *name, size_t len) {
    return sethostname(name, len);
}

int husk_open(const char *path, int flags, mode_t mode) {
    return open(path, flags, mode);
}

int husk_close(int fd) {
    return close(fd);
}

uid_t husk_getuid(void) {
    return getuid();
}

gid_t husk_getgid(void) {
    return getgid();
}

pid_t husk_getpid(void) {
    return getpid();
}

pid_t husk_fork(void) {
    return fork();
}

int husk_sigaction(
    int signum,
    const struct sigaction *act,
    struct sigaction *oldact
) {
    return sigaction(signum, act, oldact);
}

int husk_sigemptyset(sigset_t *set) {
    return sigemptyset(set);
}

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

