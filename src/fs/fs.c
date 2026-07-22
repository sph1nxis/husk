#include "fs/fs.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common/error.h"
#include "log/log.h"
#include "sys/sys.h"

Result fs_write_file(const char *path, const char *content) {
    int fd = sys_open(path, O_WRONLY, 0);

    if (fd < 0) {
        return system_error("open(%s)", path);
    }

    ssize_t len = strlen(content);

    if (sys_write(fd, content, len) != len) {
        return system_error("open(%s)", path);
    }

    close(fd);
    return kResultOk;
}

Result fs_exists(const char *path) {
    struct stat st;

    if (sys_stat(path, &st) == 0) {
        return kResultOk;
    }

    if (errno == ENOENT) {
        return kResultNotFound;
    }

    return system_error("stat(%s)", path);
}

Result fs_is_directory(const char *path) {
    struct stat st;

    if (sys_stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return kResultOk;
        }
        return kResultNotDirectory;
    }

    if (errno == ENOENT) {
        return kResultNotDirectory;
    }

    return system_error("stat(%s)", path);
}

Result fs_mkdir(const char *path, mode_t mode) {
    if (sys_mkdir(path, mode) < 0) {
        return system_error("mkdir(%s)", path);
    }

    return kResultOk;
}

Result fs_ensure_directory(const char *path, mode_t mode) {
    Result exists = fs_exists(path);

    if (exists != kResultOk && exists != kResultNotFound) {
        return exists;
    }

    if (exists == kResultOk) {
        Result is_dir = fs_is_directory(path);

        if (is_dir == kResultSystemError) {
            return is_dir;
        }

        if (is_dir != kResultOk) {
            log_error("%s exists but is not a directory", path);
            return kResultNotDirectory;
        }

        return kResultOk;
    }

    return fs_mkdir(path, mode);
}

