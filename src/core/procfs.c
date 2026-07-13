#include "core/procfs.h"

#include <stddef.h>

#include "sys/sys.h"
#include "utils/log.h"

Result procfs_setup(void) {
    if (sys_mount("proc", "/proc", "proc", 0, NULL) < 0) {
        log_errno("mount(proc)");
        return result_errno_to_result();
    }

    return kResultOk;
}

