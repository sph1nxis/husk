#include "process/init_process.h"

#include <errno.h>
#include <limits.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "log/log.h"
#include "process/process.h"
#include "sys/sys.h"

static const char *signal_name(int sig) {
    switch (sig) {

        case SIGABRT:
            return "SIGABRT";

        case SIGALRM:
            return "SIGALRM";

        case SIGBUS:
            return "SIGBUS";

        case SIGCHLD:
            return "SIGCHLD";

        case SIGCONT:
            return "SIGCONT";

        case SIGFPE:
            return "SIGFPE";

        case SIGHUP:
            return "SIGHUP";

        case SIGILL:
            return "SIGILL";

        case SIGINT:
            return "SIGINT";

        case SIGKILL:
            return "SIGKILL";

        case SIGPIPE:
            return "SIGPIPE";

        case SIGQUIT:
            return "SIGQUIT";

        case SIGSEGV:
            return "SIGSEGV";

        case SIGSTOP:
            return "SIGSTOP";

        case SIGTERM:
            return "SIGTERM";

        case SIGTSTP:
            return "SIGTSTP";

        case SIGTTIN:
            return "SIGTTIN";

        case SIGTTOU:
            return "SIGTTOU";

        case SIGUSR1:
            return "SIGUSR1";

        case SIGUSR2:
            return "SIGUSR2";

        case SIGSYS:
            return "SIGSYS";

        case SIGTRAP:
            return "SIGTRAP";

        case SIGURG:
            return "SIGURG";

        case SIGXCPU:
            return "SIGXCPU";

        case SIGXFSZ:
            return "SIGXFSZ";

        case SIGVTALRM:
            return "SIGVTALRM";

        case SIGPROF:
            return "SIGPROF";

        case SIGWINCH:
            return "SIGWINCH";

        case SIGIO:
            return "SIGIO";

        case SIGPWR:
            return "SIGPWR";

#ifdef SIGEMT
        case SIGEMT:
            return "SIGEMT";
#endif

#ifdef SIGSTKFLT
        case SIGSTKFLT:
            return "SIGSTKFLT";
#endif

        default:
            return "UNKNOWN";

    }
}

static void sigchld_handler(int signo) {
    (void) signo;
}

static int handle_child_exit(pid_t main_pid, pid_t pid, int status) {
    if (pid == main_pid) {
        if (WIFEXITED(status)) {
            log_info("main process exited with status %d", WEXITSTATUS(status));
            return WEXITSTATUS(status);
        }

        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            if (sig == SIGINT || sig == SIGTERM) {
                    log_info(
                    "main process terminated by signal %d (%s)", 
                    sig,
                    signal_name(sig)
                );
            } else {
                log_warn(
                    "main process killed by signal %d (%s)", 
                    sig,
                    signal_name(sig)
                );
            }
            return 128 + sig;
        }

        log_warn("main process terminated unexpectedly (status=%d)", status);
        return EXIT_FAILURE;
    }
    
    if (WIFEXITED(status)) {
        log_info(
            "child pid=%d exited with status %d",
            pid,
            WEXITSTATUS(status)
        );
    } else if (WIFSIGNALED(status)) {
        log_info(
            "child pid=%d killed by signal %d", 
            pid,
            WTERMSIG(status)
        );
    } else {
        log_info("child pid=%d terminated", pid);
    }
    return -1;
}

int init_process_run(const container_config *config) {
    struct sigaction sa = {0};
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

    pid_t main_pid = process_spawn(config);

    if (main_pid < 0) {
        return EXIT_FAILURE;
    }

    log_info("main process started (pid=%d)", main_pid);

    for (;;) {
        int status;
        pid_t pid = sys_waitpid(-1, &status, 0);

        if (pid < 0) {
            if (errno == EINTR) {
                continue;
            }
            log_errno("waitpid");
            return EXIT_FAILURE;
        }

        int ret = handle_child_exit(main_pid, pid, status);
        
        if (ret >= 0) {
            return ret;
        }
    }
}

