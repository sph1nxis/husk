#include "core/environment.h"
#include "core/result.h"

#include <stdlib.h>

Result environment_setup(const container_config *config) {
    (void) config;

    int rc = setenv(
        "PATH",
        "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
        1
    );

    if (rc < 0) {
        return result_errno_to_result();
    }
    return rc;
}

