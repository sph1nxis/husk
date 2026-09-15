#include "libc/memory.h"

#include <string.h>

void *husk_memset(void *dest, int c, size_t count) {
    return memset(dest, c, count);
}

