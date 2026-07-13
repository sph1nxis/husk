#include "rootfs/rootfs_layout.h"

#include <limits.h>
#include <stdio.h>

#include "fs/fs.h"
#include "fs/path.h"
#include "utils/util.h"

typedef struct {
    const char *path;
    mode_t mode;
} rootfs_directory;

static const rootfs_directory directories[] = {
    { "proc", 0555 },
    { "dev", 0755 },
    { "sys", 0555 },
    { "tmp", 01777 },
    { "run", 0755 },
    { "mnt", 0755 },
    { "media", 0755 },
};

static Result ensure_directory(
    const container_config *config,
    const char *directory,
    mode_t mode
) {
    char path[PATH_MAX];

    Result rc = path_join(path, sizeof(path), config->rootfs, directory);
    if (rc != kResultOk) {
        return rc;
    }

    return fs_ensure_directory(path, mode);
}

Result rootfs_prepare_layout(const container_config *config) {
    if (config->rootfs == NULL) {
        return kResultOk;
    }

    for (size_t i = 0; i < ARRAY_SIZE(directories); ++i) {
        Result rc = ensure_directory(
            config,
            directories[i].path,
            directories[i].mode
        );

        if (rc != kResultOk) {
            return rc;
        }
    }

    return kResultOk;
}

