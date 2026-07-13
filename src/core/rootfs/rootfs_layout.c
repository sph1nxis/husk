#include "core/rootfs/rootfs_layout.h"

#include <limits.h>
#include <stdio.h>

#include "utils/fs.h"
#include "utils/path.h"
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

static int ensure_directory(
    const container_config *config,
    const char *directory,
    mode_t mode
) {
    char path[PATH_MAX];

    if (path_join(path, sizeof(path), config->rootfs, directory) < 0) {
        return -1;
    }

    return fs_ensure_directory(path, mode);
}

int rootfs_prepare_layout(const container_config *config) {
    if (config->rootfs == NULL) {
        return 0;
    }

    for (size_t i = 0; i < ARRAY_SIZE(directories); ++i) {
        if (ensure_directory(config, directories[i].path, directories[i].mode) < 0) {
            return -1;
        }
    }

    return 0;
}

