#pragma once

#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

pid_t husk_clone(int (*fn)(void *), void *stack, int flags, void *arg);

int husk_pipe(int pipefd[2]);

ssize_t husk_read(int fd, void *buf, size_t count);

ssize_t husk_write(int fd, const void *buf, size_t count);

pid_t husk_waitpid(pid_t pid, int *status, int options);

int husk_execvp(const char *file, char *const argv[]);

int husk_sethostname(const char *name, size_t len);

int husk_open(const char *path, int flags, mode_t mode);

int husk_close(int fd);

uid_t husk_getuid(void);

gid_t husk_getgid(void);

pid_t husk_getpid(void);

pid_t husk_fork(void);

int husk_sigaction(
    int signum,
    const struct sigaction *act,
    struct sigaction *oldact
);

int husk_sigemptyset(sigset_t *set);

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

