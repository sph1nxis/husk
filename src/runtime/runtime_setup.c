#include "runtime/runtime_setup.h"

#include <stddef.h>

#include "namespace/mount_namespace.h"
#include "namespace/procfs.h"
#include "namespace/uts_namespace.h"
#include "rootfs/rootfs.h"
#include "runtime/environment.h"
#include "utils/util.h"

typedef Result (*setup_stage_fn)(const container_config *);

typedef struct {
    const char *name;
    setup_stage_fn fn;
} setup_stage;

static const setup_stage stages[] = {
    { "environment", environment_setup },
    { "uts", uts_namespace_setup },
    { "mount", mount_namespace_setup },
    { "rootfs", rootfs_prepare },
    { "rootfs", rootfs_enter },
    { "procfs", procfs_setup },
};

Result container_setup(const container_config *config) {
    for (size_t i = 0; i < ARRAY_SIZE(stages); ++i) {
        const setup_stage_fn fn = stages[i].fn;
        Result rc = fn(config);

        if (rc != kResultOk) {
            return rc;
        }
    }

    return kResultOk;
}

