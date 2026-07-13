#pragma once

#include <sys/types.h>

#include "core/result.h"

Result fs_write_file(const char *path, const char *content);

Result fs_exists(const char *path);

Result fs_is_directory(const char *path);

Result fs_mkdir(const char *path, mode_t mode);

Result fs_ensure_directory(const char *path, mode_t mode);

