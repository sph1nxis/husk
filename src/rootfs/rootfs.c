#include "rootfs/rootfs.h"

#include "rootfs/chroot_rootfs.h"

static const rootfs_ops *ops = &chroot_rootfs_ops;

Result rootfs_prepare(const container_config *config) {
    Result rc =ops->prepare(config);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

Result rootfs_enter(const container_config *config) {
    Result rc = ops->activate(config);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

Result rootfs_cleanup(const container_config *config) {
    Result rc = ops->cleanup(config);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

