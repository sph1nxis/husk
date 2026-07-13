#pragma once

#include "core/container_config.h"
#include "core/result.h"

typedef struct {
    Result (*activate)(const container_config *);
    Result (*cleanup)(const container_config *);
} rootfs_ops;

Result rootfs_setup(const container_config *config);

