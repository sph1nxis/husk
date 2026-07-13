#include "namespace/mount_namespace.h"

#include <sys/mount.h>

#include "sys/sys.h"
#include "utils/log.h"

Result mount_namespace_setup(const container_config *config) {
    (void) config;

    if (sys_mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL) < 0) {
        log_errno("mount(MS_PRIVATE)");
        return result_errno_to_result();
    }

    return kResultOk;
}

