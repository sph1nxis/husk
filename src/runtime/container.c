#define _GNU_SOURCE

#include "runtime/container.h"

#include <limits.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "log/log.h"
#include "namespace/user_namespace.h"
#include "process/init_process.h"
#include "rootfs/rootfs.h"
#include "runtime/runtime_setup.h"
#include "sys/sys.h"

enum {
    kStackSize = 1024 * 1024
};

static char child_stack[kStackSize];

typedef struct {
    const container_config *config;
    int pipe_fd[2];
} child_config;

static int child_main(void *arg) {
    child_config *child_cfg = arg;

    sys_close(child_cfg->pipe_fd[1]);

    char sync;
    ssize_t ret = sys_read(child_cfg->pipe_fd[0], &sync, 1);

    if (ret < 0) {
        log_errno("read sync pipe");
        sys_close(child_cfg->pipe_fd[0]);
        return EXIT_FAILURE;
    }

    if (ret != 1) {
        log_error("failed to synchronize with parent (unexpected EOF)");
        sys_close(child_cfg->pipe_fd[0]);
        return EXIT_FAILURE;
    }

    sys_close(child_cfg->pipe_fd[0]);

    if (container_setup(child_cfg->config) < 0) {
        return EXIT_FAILURE;
    }

    int rc = init_process_run(child_cfg->config);

    Result cleanup_rc = rootfs_cleanup(child_cfg->config);
    if (cleanup_rc != kResultOk) {
        log_error("rootfs cleanup failed: %s", result_string(cleanup_rc));
    }

    return rc;
}

int container_run(const container_config *config) {
    child_config child_cfg = {
        .config = config,
    };

    if (sys_pipe(child_cfg.pipe_fd) < 0) {
        log_errno("pipe");
        return EXIT_FAILURE;
    }

    int flags = config->namespaces | SIGCHLD;

    pid_t pid = sys_clone(
        child_main,
        child_stack + kStackSize,
        flags,
        &child_cfg
    );

    if (pid < 0) {
        sys_close(child_cfg.pipe_fd[0]);
        sys_close(child_cfg.pipe_fd[1]);

        log_errno("clone");
        return EXIT_FAILURE;
    }

    log_info("created container process pid=%d", pid);

    sys_close(child_cfg.pipe_fd[0]);

    log_info("configuring user namespace");

    if (user_namespace_setup(pid) < 0) {
        sys_close(child_cfg.pipe_fd[1]);
        sys_waitpid(pid, NULL, 0);
        return EXIT_FAILURE;
    }

    log_info("user namespace configured");

    if (sys_write(child_cfg.pipe_fd[1], "x", 1) != 1) {
        log_errno("write (sync)");
        sys_close(child_cfg.pipe_fd[1]);

        sys_waitpid(pid, NULL, 0);

        return EXIT_FAILURE;
    }

    sys_close(child_cfg.pipe_fd[1]);

    int status;

    if (sys_waitpid(pid, &status, 0) < 0) {
        log_errno("waitpid");
        return EXIT_FAILURE;
    }

    log_info("container exited");

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return EXIT_FAILURE;
}

