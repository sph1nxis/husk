#include "namespace/procfs.h"

#include <stddef.h>

#include "common/error.h"
#include "sys/sys.h"

Result procfs_setup(const container_config *config) {
    (void) config;

    if (sys_mount("proc", "/proc", "proc", 0, NULL) < 0) {
        return system_error("mount(proc)");
    }

    return kResultOk;
}

