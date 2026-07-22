#pragma once

#include "common/result.h"
#include "runtime/container_config.h"

typedef struct {
    const char *rootfs;
    const char *hostname;
    char **command;
} cli_options;

Result cli_parse(int argc, char **argv, cli_options *options);

void cli_print_help(const char *program);

Result cli_apply(const cli_options *options, container_config *config);

