#include "core/user_namespace.h"

#include <limits.h>

#include "sys/sys.h"
#include "utils/fs.h"
#include "utils/path.h"

static Result write_setgroups(pid_t pid) {
    char path[PATH_MAX];
    Result rc;

    rc = path_printf(path, sizeof(path), "/proc/%d/setgroups", pid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = fs_write_file(path, "deny");
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

static Result write_uid_map(pid_t pid) {
    char path[PATH_MAX];
    char map[256];
    uid_t uid = sys_getuid();
    Result rc;

    rc = path_printf(path, sizeof(path), "/proc/%d/uid_map", pid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = path_printf(map, sizeof(map), "0 %d 1\n", uid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = fs_write_file(path, map);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

static Result write_gid_map(pid_t pid) {
    char path[PATH_MAX];
    char map[256];
    gid_t gid = sys_getgid();
    Result rc;

    rc = path_printf(path, sizeof(path), "/proc/%d/gid_map", pid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = path_printf(map, sizeof(map), "0 %d 1\n", gid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = fs_write_file(path, map);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

Result user_namespace_setup(pid_t pid) {
    Result rc;

    rc = write_setgroups(pid);
    if (rc != kResultOk) {
        return rc;
    }

    rc = write_uid_map(pid);
    if (rc != kResultOk) {
        return rc;
    }
    
    rc = write_gid_map(pid);
    if (rc != kResultOk) {
        return rc;
    }

    return kResultOk;
}

