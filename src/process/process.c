#include "process/process.h"

#include <stdlib.h>

#include "sys/sys.h"
#include "utils/log.h"

int process_exec(const container_config *config) {
    log_info("executing %s", config->argv[0]);

    sys_execvp(config->argv[0], config->argv);

    log_errno("execvp(%s)", config->argv[0]);

    return EXIT_FAILURE;
}

pid_t process_spawn(const container_config *config) {
    pid_t pid = sys_fork();

    if (pid < 0) {
        log_errno("fork");
        return -1;
    }

    if (pid == 0) {
        return process_exec(config);
    }

    return pid;
}

