# husk

A minimal rootless container runtime for Linux x86_64 written in C17.

The project is built from scratch without Docker, runc or other container runtimes to demonstrate how Linux containers work internally using namespaces, `chroot`, `procfs`, UID/GID mappings and low-level Linux APIs.

System calls are isolated behind an abstraction layer, allowing C implementations to be replaced with x86-64 Assembly without changing the public interfaces.

## Features

- Rootless containers using User Namespace
- PID, UTS and Mount namespaces
- UID/GID mapping
- `chroot`-based RootFS
- Private mount namespace
- Separate `procfs` mount
- PID 1 init process with child reaping
- Modular runtime architecture
- Unified error handling
- Linux API abstraction layer

## Build

Requirements:

- Linux x86_64
- GCC
- CMake 3.16+

Build:

```bash
cmake -B build
cmake --build build
```

## Usage

```bash
# inside build/
./husk /bin/sh
```

## Architecture

Project structure:

- `common/`
  - Shared types and error handling
- `fs/`
  - Filesystem and path utilities
- `namespace/`
  - User, PID, UTS, Mount namespace setup and `procfs`
- `process/`
  - Container init process and process management
- `rootfs/`
  - Root filesystem abstraction and implementations
- `runtime/`
  - Container lifecycle and runtime orchestration
- `sys/`
  - Linux API abstraction layer
- `utils/`
  - Logging and common utilities

## Plans 

- CLI
- x86-64 Assembly syscall wrappers
- Assembly implementations of libc functions 
- `clone()` trampoline in Assembly
- `pivot_root` RootFS strategy

