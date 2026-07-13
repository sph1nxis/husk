#include "core/rootfs/rootfs.h"

#include "core/rootfs/chroot_rootfs.h"
#include "core/rootfs/rootfs_layout.h"

static const rootfs_ops *ops = &chroot_rootfs_ops;

Result rootfs_setup(const container_config *config) {
    Result rc =  rootfs_prepare_layout(config);
    if (rc != kResultOk) {
        return rc;
    }

    rc = ops->activate(config) != kResultOk;
    if (rc != kResultOk) {
        return rc;
    }

    rc = ops->cleanup(config) != kResultOk;
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

