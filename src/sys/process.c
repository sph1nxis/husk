#define _GNU_SOURCE

#include "sys/process.h"

#include <sched.h>
#include <sys/wait.h>

pid_t husk_clone(int (*fn)(void *), void *stack, int flags, void *arg) {
    return clone(fn, stack, flags, arg);
}

pid_t husk_waitpid(pid_t pid, int *status, int options) {
    return waitpid(pid, status, options);
}

int husk_execvp(const char *file, char *const argv[]) {
    return execvp(file, argv);
}

pid_t husk_fork(void) {
    return fork();
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

