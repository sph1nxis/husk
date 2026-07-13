#include "core/container_setup.h"

#include "core/environment.h"
#include "core/mount_namespace.h"
#include "core/procfs.h"
#include "core/rootfs/rootfs.h"
#include "core/uts_namespace.h"

int container_setup(const container_config *config) {
    if (environment_setup(config) < 0) {
        return -1;
    }


    if (uts_namespace_setup(config) < 0) {
        return -1;
    }


    if (mount_namespace_setup() < 0) {
        return -1;
    }


    if (rootfs_setup(config) < 0) {
        return -1;
    }

    if (procfs_setup() < 0) {
        return -1;
    }

    return 0;
}
