#include "namespace/uts_namespace.h"

#include "libc/string.h"
#include "sys/sys.h"

Result uts_namespace_setup(const container_config *config) {
    if (husk_sethostname(config->hostname, husk_strlen(config->hostname)) < 0) {
        return result_errno_to_result();
    }

    return kResultOk;
}

