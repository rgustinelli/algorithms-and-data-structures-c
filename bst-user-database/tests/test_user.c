/**
 * @file test_user.c
 * @brief Assert-based tests for the User module.
 */
#include "user.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_create_stores_fields(void) {
    User* user = user_create(42U, "user@example.com", "Alice", "s3cr3t");

    assert(user->id == 42U);
    assert(strcmp(user->email, "user@example.com") == 0);
    assert(strcmp(user->name, "Alice") == 0);
    assert(strcmp(user->password, "s3cr3t") == 0);

    user_destroy(user);
}

static void test_create_truncates_long_strings(void) {
    /*
     * user->email/name/password are fixed-size 256-byte buffers. Strings
     * longer than 255 characters must be truncated by user_create(),
     * never overflow the buffer.
     */
    char long_value[512];
    memset(long_value, 'x', sizeof(long_value) - 1);
    long_value[sizeof(long_value) - 1] = '\0';

    User* user = user_create(1U, long_value, long_value, long_value);

    assert(strlen(user->email) == 255);
    assert(strlen(user->name) == 255);
    assert(strlen(user->password) == 255);

    user_destroy(user);
}

int main(void) {
    test_create_stores_fields();
    test_create_truncates_long_strings();

    printf("test_user: all tests passed\n");
    return 0;
}
