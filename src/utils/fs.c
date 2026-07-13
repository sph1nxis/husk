#include "utils/fs.h"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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
    return sys_stat(path, &st) == 0;
}

int fs_is_directory(const char *path) {
    struct stat st;

    if (sys_stat(path, &st) < 0) {
        return 0;
    }

    return S_ISDIR(st.st_mode);
}

int fs_mkdir(const char *path, mode_t mode) {
    if (sys_mkdir(path, mode) < 0) {
        log_errno("mkdir(%s)", path);
        return -1;
    }

    return 0;
}

int fs_ensure_directory(const char *path, mode_t mode) {
    if (fs_exists(path)) {
        if (!fs_is_directory(path)) {
            log_error("%s exists but is not a directory", path);
            return -1;
        }
        return 0;
    }

    return fs_mkdir(path, mode);
}

