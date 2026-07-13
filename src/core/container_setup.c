#include "core/container_setup.h"

#include "core/environment.h"
#include "core/mount_namespace.h"
#include "core/procfs.h"
#include "core/rootfs/rootfs.h"
#include "core/uts_namespace.h"

Result container_setup(const container_config *config) {
    Result rc;

    rc = environment_setup(config);
    if (rc != kResultOk) {
        return rc;
    }

    rc = uts_namespace_setup(config);
    if (rc != kResultOk) {
        return rc;
    }

    rc = mount_namespace_setup();
    if (rc != kResultOk) {
        return rc;
    }

    rc = rootfs_setup(config);
    if (rc != kResultOk) {
        return rc;
    }

    rc = procfs_setup() < 0;
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

