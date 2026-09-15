#include "sys/namespace.h"

#include <unistd.h>

int husk_sethostname(const char *name, size_t len) {
    return sethostname(name, len);
}

