#include "namespace/mount_namespace.h"

#include <sys/mount.h>

#include "common/error.h"
#include "sys/sys.h"

Result mount_namespace_setup(const container_config *config) {
    (void) config;

    if (sys_mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL) < 0) {
        return system_error("mount(MS_PRIVATE)");
    }

    return kResultOk;
}

