#include "utils/fs.h"

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "sys/sys.h"
#include "utils/log.h"

Result fs_write_file(const char *path, const char *content) {
    int fd = sys_open(path, O_WRONLY, 0);

    if (fd < 0) {
        log_errno("open(%s)", path);
        return result_errno_to_result();
    }

    ssize_t len = strlen(content);

    if (sys_write(fd, content, len) != len) {
        log_errno("write(%s)", path);
        sys_close(fd);
        return result_errno_to_result();
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

    log_errno("stat(%s)", path);

    return kResultSystemError;
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

    log_errno("stat(%s)", path);

    return kResultSystemError;
}

Result fs_mkdir(const char *path, mode_t mode) {
    if (sys_mkdir(path, mode) < 0) {
        log_errno("mkdir(%s)", path);
        return result_errno_to_result();
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

