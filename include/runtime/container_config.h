#pragma once

#include "common/result.h"

typedef enum {
    kContainerConfigBuilding,
    kContainerConfigBuilt,
} ContainerConfigState;

typedef struct {
    char **argv;             /* command to execute */

    const char *hostname;    /* container hostname */
    const char *rootfs;      /* root filesystem */

    unsigned int namespaces; /* clone namespace flags */
    
    ContainerConfigState state; /* config state */
} container_config;

void container_config_init(container_config *config);

Result container_config_set_command(container_config *config, char **argv);
Result container_config_set_hostname(container_config *config, const char *hostname);
Result container_config_set_rootfs(container_config *config, const char *rootfs);

Result container_config_enable_namespace(container_config *config, unsigned int ns);

Result container_config_build(container_config *config);

