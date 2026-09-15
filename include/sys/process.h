#pragma once

#include <fcntl.h>
#include <unistd.h>

pid_t husk_clone(int (*fn)(void *), void *stack, int flags, void *arg);

pid_t husk_waitpid(pid_t pid, int *status, int options);

int husk_execvp(const char *file, char *const argv[]);

pid_t husk_fork(void);

uid_t husk_getuid(void);

gid_t husk_getgid(void);

pid_t husk_getpid(void);

