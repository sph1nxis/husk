#include "core/container_config.h"

#include <stdlib.h>

#include "utils/log.h"

void container_config_init(container_config *config) {
    config->argv = NULL;
    config->hostname = "husk";
    config->rootfs = NULL;
    config->namespaces = 0;
}

Result container_config_set_command(container_config *config, char **argv) {
    config->argv = argv;
    return kResultOk;
}

Result container_config_set_hostname(container_config *config, const char *hostname) {
    config->hostname = hostname;
    return kResultOk;
}

Result container_config_set_rootfs(container_config *config, const char *rootfs) {
    config->rootfs = rootfs;
    return kResultOk;
}

Result container_config_enable_namespace(container_config *config, unsigned int ns) {
    config->namespaces |= ns;
    return kResultOk;
}

Result container_config_build(container_config *config) {
    if (config->argv == NULL) {
        log_error("no command specified");
        return kResultInvalidArgument;
    }
    return kResultOk;
}

