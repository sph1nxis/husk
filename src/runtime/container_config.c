#include "runtime/container_config.h"

#include <limits.h>
#include <string.h>

#include "utils/log.h"

void container_config_init(container_config *config) {
    config->state = kContainerConfigBuilding;
    config->argv = NULL;
    config->hostname = "husk";
    config->rootfs = NULL;
    config->namespaces = 0;
}

Result container_config_set_command(container_config *config, char **argv) {
    if (config->state != kContainerConfigBuilding) {
        return kResultInvalidState;
    }

    config->argv = argv;

    return kResultOk;
}

Result container_config_set_hostname(container_config *config, const char *hostname) {
    if (config->state != kContainerConfigBuilding) {
        return kResultInvalidState;
    }

    config->hostname = hostname;

    return kResultOk;
}

Result container_config_set_rootfs(container_config *config, const char *rootfs) {
    if (config->state != kContainerConfigBuilding) {
        return kResultInvalidState;
    }

    config->rootfs = rootfs;

    return kResultOk;
}

Result container_config_enable_namespace(container_config *config, unsigned int ns) {
    if (config->state != kContainerConfigBuilding) {
        return kResultInvalidState;
    }

    config->namespaces |= ns;

    return kResultOk;
}

Result container_config_build(container_config *config) {
    if (config->state != kContainerConfigBuilding) {
        log_error("container config is not in building state");
        return kResultInvalidState;
    }

    if (config->argv == NULL) {
        log_error("no command specified");
        return kResultInvalidArgument;
    }

    if (config->hostname == NULL) {
        log_error("no hostname specified");
        return kResultInvalidArgument;
    }

    if (config->rootfs == NULL) {
        log_error("no rootfs specified");
        return kResultInvalidArgument;
    }
    
    if (strlen(config->hostname) > HOST_NAME_MAX) {
        log_error("hostname is too long");
        return kResultInvalidArgument;
    }

    config->state = kContainerConfigBuilt;

    return kResultOk;
}

