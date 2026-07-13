#include "utils/fs.h"

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "sys/sys.h"
#include "utils/log.h"

int fs_write_file(const char *path, const char *content) {
    int fd = sys_open(path, O_WRONLY, 0);

    if (fd < 0) {
        log_errno("open(%s)", path);
        return -1;
    }

    ssize_t len = strlen(content);

    if (sys_write(fd, content, len) != len) {
        log_errno("write(%s)", path);
        sys_close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int fs_exists(const char *path) {
    struct stat st;

    if (sys_stat(path, &st) == 0) {
        return 1;
    }

    if (errno == ENOENT) {
        return 0;
    }

    log_errno("stat(%s)", path);

    return -1;
}

int fs_is_directory(const char *path) {
    struct stat st;

    if (sys_stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return 1;
        }
        return 0;
    }

    if (errno == ENOENT) {
        return 0;
    }

    log_errno("stat(%s)", path);

    return -1;
}

int fs_mkdir(const char *path, mode_t mode) {
    if (sys_mkdir(path, mode) < 0) {
        log_errno("mkdir(%s)", path);
        return -1;
    }

    return 0;
}

int fs_ensure_directory(const char *path, mode_t mode) {
    int exists = fs_exists(path);

    if (exists < 0) {
        return -1;
    }

    if (exists) {
        int is_dir = fs_is_directory(path);

        if (is_dir < 0) {
            return -1;
        }

        if (!is_dir) {
            log_error("%s exists but is not a directory", path);
            return -1;
        }

        return 0;
    }

    return fs_mkdir(path, mode);
}

