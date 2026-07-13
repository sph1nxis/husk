#include "core/uts_namespace.h"

#include <string.h>

#include "sys/sys.h"

Result uts_namespace_setup(const container_config *config) {
    if (sys_sethostname(config->hostname, strlen(config->hostname)) < 0) {
        return result_errno_to_result();
    }

    return kResultOk;
}

