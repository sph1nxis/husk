#pragma once

#include <sys/types.h>

int fs_write_file(const char *path, const char *content);

int fs_exists(const char *path);

int fs_is_directory(const char *path);

int fs_mkdir(const char *path, mode_t mode);

int fs_ensure_directory(const char *path, mode_t mode);

