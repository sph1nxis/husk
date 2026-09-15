#include "libc/string.h"

#include <string.h>

size_t husk_strlen(const char *str) {
    return strlen(str);
}

int husk_strcmp(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

