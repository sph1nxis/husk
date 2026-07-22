#include "rootfs/chroot_rootfs.h"

#include <stdio.h>

#include "common/error.h"
#include "common/result.h"
#include "rootfs/rootfs.h"
#include "rootfs/rootfs_layout.h"
#include "runtime/container_config.h"
#include "sys/sys.h"

static Result prepare(const container_config *config) {
    return rootfs_prepare_layout(config);
}

static Result activate(const container_config *config) {
    if (config->rootfs == NULL) {
        return kResultOk;
    }

    if (sys_chroot(config->rootfs) < 0) {
        return system_error("chroot");
    }

    if (sys_chdir("/") < 0) {
        return system_error("chdir");
    }
    return kResultOk;
}

static Result cleanup(const container_config *config) {
    (void) config;
    return kResultOk;
}

const rootfs_ops chroot_rootfs_ops = {
    .prepare = prepare,
    .activate = activate,
    .cleanup = cleanup,
};

