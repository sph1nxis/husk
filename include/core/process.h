#pragma once

#include <sys/types.h>

#include "core/container_config.h"

pid_t process_spawn(const container_config *config);

int process_exec(const container_config *config);

