#pragma once

#include <signal.h>

int husk_sigaction(
    int signum,
    const struct sigaction *act,
    struct sigaction *oldact
);

int husk_sigemptyset(sigset_t *set);

