#include "core/init_process.h"

#include <errno.h>
#include <limits.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sys/sys.h"
#include "utils/log.h"

static void sigchld_handler(int signo) {
    (void) signo;
}

int init_process_run(const container_config *config) {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchld_handler;

    if (sys_sigemptyset(&sa.sa_mask) < 0) {
        log_errno("sigemptyset");
        return EXIT_FAILURE;
    }

    sa.sa_flags = SA_RESTART;

    if (sys_sigaction(SIGCHLD, &sa, NULL) < 0) {
        log_errno("sigaction");
        return EXIT_FAILURE;
    }

    pid_t main_pid = sys_fork();

    if (main_pid < 0) {
        log_errno("fork");
        return EXIT_FAILURE;
    }

    if (main_pid == 0) {
        log_info("executing %s", config->argv[0]);

        sys_execvp(config->argv[0], config->argv);

        log_errno("execvp(%s)", config->argv[0]);
        return EXIT_FAILURE;
    }

    int status;

    for (;;) {
        pid_t pid = sys_waitpid(-1, &status, 0);

        if (pid < 0) {
            if (errno == EINTR) {
                continue;
            }

            log_errno("waitpid");
            return EXIT_FAILURE;
        }

        if (pid != main_pid) {
            continue;
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        }

        return EXIT_FAILURE;
    }
}

