#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli/cli.h"
#include "common/result.h"
#include "log/log.h"
#include "runtime/container.h"
#include "runtime/container_config.h"

int main(int argc, char **argv) {
    if (log_init("husk.log") != kResultOk) {
        fprintf(stderr, "failed to initialize logging\n");
        return EXIT_FAILURE;
    }

    cli_options options;

    Result status = cli_parse(argc, argv, &options);
    
    if (status == kResultExitSuccess) {
        log_close();
        return EXIT_SUCCESS;
    }

    if (status != kResultOk) {
        log_close();
        return EXIT_FAILURE;
    }

    container_config config;

    container_config_init(&config);
    container_config_defaults(&config);

    status = cli_apply(&options, &config);

    if (status != kResultOk) {
        log_close();
        return EXIT_FAILURE;
    }

    int rc = container_run(&config);

    log_close();

    return rc;
}

