/**
 * @file user.c
 * @brief User record implementation.
 */
#include "user.h"

#include <stdio.h>
#include <stdlib.h>

void user_print(User* user) {
    printf("%u, %s, %s, %s\n", user->id, user->email, user->name, user->password);
}

User* user_create(unsigned int id, const char* email, const char* name, const char* password) {
    User* user = malloc(sizeof(User));

    user->id = id;
    snprintf(user->email, sizeof(user->email), "%s", email);
    snprintf(user->name, sizeof(user->name), "%s", name);
    snprintf(user->password, sizeof(user->password), "%s", password);

    return user;
}

void user_destroy(User* user) {
    free(user);
}
