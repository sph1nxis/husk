#pragma once

#include "core/container_config.h"
#include "core/result.h"

typedef struct {
    Result (*prepare)(const container_config *config);
    Result (*activate)(const container_config *config);
    Result (*cleanup)(const container_config *config);
} rootfs_ops;

Result rootfs_prepare(const container_config *config);
Result rootfs_enter(const container_config *config);
Result rootfs_cleanup(const container_config *config);

