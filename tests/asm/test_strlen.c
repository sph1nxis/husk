#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asm/string.h"

static void test_empty(void) {
    assert(asm_strlen("") == 0);
    assert(asm_strlen("") == strlen(""));
}

static void test_single_char(void) {
    assert(asm_strlen("a") == 1);
    assert(asm_strlen("a") == strlen("a"));
    assert(asm_strlen("Z") == 1);
    assert(asm_strlen("9") == 1);
}

static void test_word(void) {
    assert(asm_strlen("hello") == 5);
    assert(asm_strlen("hello") == strlen("hello"));
}

static void test_sentence(void) {
    const char *s = "The quick brown fox jumps over the lazy dog";
    assert(asm_strlen(s) == 43);
    assert(asm_strlen(s) == strlen(s));
}

static void test_long(void) {
    const char *s =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    assert(asm_strlen(s) == 62);
    assert(asm_strlen(s) == strlen(s));
}

static void test_special_chars(void) {
    assert(asm_strlen("\0") == 0);
    assert(asm_strlen("\n") == 1);
    assert(asm_strlen("\t") == 1);
    assert(asm_strlen("\\") == 1);
    assert(asm_strlen("\"") == 1);

    const char *s = "line1\nline2\tindented";
    assert(asm_strlen(s) == strlen(s));
}

static void test_unicode(void) {
    const char *s = "хéllo wörld! 世界";
    assert(asm_strlen(s) == strlen(s));
}

static void test_very_long_string(void) {
    size_t n = 10000;
    char *s = (char *) malloc(n + 1);
    assert(s != NULL);

    memset(s, 'x', n);
    s[n] = '\0';

    assert(asm_strlen(s) == n);
    assert(asm_strlen(s) == strlen(s));

    free(s);
}

static void test_zero_terminated(void) {
    char buf[128];

    strcpy(buf, "hello");
    buf[2] = '\0';
    assert(asm_strlen(buf) == 2);
    assert(asm_strlen(buf) == strlen(buf));
}

static void test_embedded_nulls(void) {
    const char *s = "abc\0def\0ghi";
    assert(asm_strlen(s) == 3);
    assert(asm_strlen(s) == strlen(s));
}

static void test_whitespace(void) {
    assert(asm_strlen("   ") == 3);
    assert(asm_strlen("\t\t") == 2);
    assert(asm_strlen("\n\r") == 2);
    assert(asm_strlen(" \t\n\r\v") == 5);
}

static void test_all_chars(void) {
    char buf[256];
    for (int i = 0; i < 255; ++i) {
        buf[i] = (char) (i + 1);
    }
    buf[255] = '\0';

    assert(asm_strlen(buf) == 255);
    assert(asm_strlen(buf) == strlen(buf));
}

int main(void) {
    printf("Running strlen tests...\n");

    printf("  Basic tests...\n");
    test_empty();
    test_single_char();
    test_word();
    test_sentence();
    test_long();

    printf("  Edge cases...\n");
    test_special_chars();
    test_unicode();
    test_zero_terminated();
    test_embedded_nulls();
    test_whitespace();

    printf("  Advanced tests...\n");
    test_very_long_string();
    test_all_chars();

    printf("\nAll strlen tests passed successfully.\n");
    return EXIT_SUCCESS;
}

