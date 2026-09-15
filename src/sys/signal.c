#include "sys/signal.h"

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
