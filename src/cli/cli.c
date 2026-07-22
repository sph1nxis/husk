#include "cli/cli.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "common/result.h"

static void print_usage(const char *program) {
    fprintf(stderr, "Usage: %s [OPTIONS] [--] [COMMAND ...]\n", program);
    fprintf(stderr, "Try '%s --help' for more information.\n", program);
}

void cli_print_help(const char *program) {
    printf("Usage: %s [OPTIONS] [--] [COMMAND ...]\n\n", program);
    printf("Run a command in an isolated container.\n\n");
    printf("Options:\n");
    printf("  --help              Show this help message and exit\n");
    printf("  --rootfs PATH       Path to the root filesystem\n");
    printf("  --hostname NAME     Set the container hostname\n");
    printf("  --                  Following arguments are command to execute\n");
}

Result cli_parse(int argc, char **argv, cli_options *options) {
    if (options == NULL) {
        return kResultInvalidArgument;
    }

    options->rootfs = NULL;
    options->hostname = NULL;
    options->command = NULL;

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "--help") == 0) {
            cli_print_help(argv[0]);
            return kResultExitSuccess;
        } else if (strcmp(argv[i], "--rootfs") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --rootfs requires an argument\n");
                print_usage(argv[0]);
                return kResultInvalidArgument;
            }
            options->rootfs = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "--hostname") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --hostname requires an argument\n");
                print_usage(argv[0]);
                return kResultInvalidArgument;
            }
            options->hostname = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "--") == 0) {
            if (i + 1 < argc) {
                options->command = &argv[i + 1];
            }
            break;
        } else {
            fprintf(stderr, "Error: unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return kResultInvalidArgument;
        }
    }

    if (options->command == NULL && i < argc) {
        options->command = &argv[i];
    }

    return kResultOk;
}

Result cli_apply(const cli_options *options, container_config *config) {
    Result rc;

    rc = container_config_set_rootfs(config, options->rootfs);
    if (rc != kResultOk) {
        return rc;
    }

    rc = container_config_set_hostname(config, options->hostname);
    if (rc != kResultOk) {
        return rc;
    }

    rc = container_config_set_command(config, options->command);
    if (rc != kResultOk) {
        return rc;
    }

    return container_config_build(config);
}

