#include "core/rootfs/chroot_rootfs.h"

#include <string.h>

#include "core/container_config.h"
#include "core/result.h"
#include "core/rootfs/rootfs.h"
#include "sys/sys.h"
#include "utils/log.h"

static Result activate(const container_config *config) {
    if (config->rootfs == NULL) {
        return kResultOk;
    }

    if (sys_chroot(config->rootfs) < 0) {
        log_errno("chroot");
        return result_errno_to_result();
    }

    if (sys_chdir("/") < 0) {
        log_errno("chdir");
        return result_errno_to_result();
    }
    return kResultOk;
}

static Result cleanup(const container_config *config) {
    (void) config;
    return kResultOk;
}

const rootfs_ops chroot_rootfs_ops = {
    .activate = activate,
    .cleanup = cleanup,
};

