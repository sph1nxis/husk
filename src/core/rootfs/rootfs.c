#include "core/rootfs/rootfs.h"

#include "core/rootfs/chroot_rootfs.h"
#include "core/rootfs/rootfs_layout.h"

static const rootfs_ops *ops = &chroot_rootfs_ops;

int rootfs_setup(const container_config *config) {
    if (rootfs_prepare_layout(config) < 0) {
        return -1;
    }

    if (ops->activate(config) < 0) {
        return -1;
    }

    if (ops->cleanup(config) < 0) {
        return -1;
    }

    return 0;
}
