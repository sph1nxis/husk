cmake_minimum_required(VERSION 3.16)

project(husk C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

include_directories(include)

add_executable(husk
    src/cli/cli.c

    src/common/error.c
    src/common/result.c
    
    src/fs/fs.c
    src/fs/path.c
    
    src/log/log.c

    src/namespace/mount_namespace.c
    src/namespace/procfs.c
    src/namespace/user_namespace.c
    src/namespace/uts_namespace.c

    src/process/init_process.c
    src/process/process.c
    
    src/rootfs/chroot_rootfs.c
    src/rootfs/rootfs.c
    src/rootfs/rootfs_layout.c

    src/runtime/container.c
    src/runtime/container_config.c
    src/runtime/environment.c
    src/runtime/runtime_setup.c

    src/sys/sys.c

    src/main.c
)

