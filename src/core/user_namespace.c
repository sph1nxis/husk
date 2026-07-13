#include "core/user_namespace.h"

#include <limits.h>

#include "sys/sys.h"
#include "utils/fs.h"
#include "utils/path.h"

static int write_setgroups(pid_t pid) {
    char path[PATH_MAX];
    
    if (path_printf(path, sizeof(path), "/proc/%d/setgroups", pid) < 0) {
        return -1;
    }

    if (fs_write_file(path, "deny") < 0) {
        return -1;
    }
    return 0;
}

static int write_uid_map(pid_t pid) {
    char path[PATH_MAX];
    char map[256];
    uid_t uid = sys_getuid();

    if (path_printf(path, sizeof(path), "/proc/%d/uid_map", pid) < 0) {
        return -1;
    }

    if (path_printf(map, sizeof(map), "0 %d 1\n", uid) < 0) {
        return -1;
    }
    if (fs_write_file(path, map) < 0) {
        return -1;
    }
    return 0;
}

static int write_gid_map(pid_t pid) {
    char path[PATH_MAX];
    char map[256];
    gid_t gid = sys_getgid();

    if (path_printf(path, sizeof(path), "/proc/%d/gid_map", pid) < 0) {
        return -1;
    }

    if (path_printf(map, sizeof(map), "0 %d 1\n", gid) < 0) {
        return -1;
    }

    if (fs_write_file(path, map) < 0) {
        return -1;
    }

    return 0;
}

int user_namespace_setup(pid_t pid) {
    if (write_setgroups(pid) < 0) {
        return -1;
    }

    if (write_uid_map(pid) < 0) {
        return -1;
    }

    if (write_gid_map(pid) < 0) {
        return -1;
    }

    return 0;
}

