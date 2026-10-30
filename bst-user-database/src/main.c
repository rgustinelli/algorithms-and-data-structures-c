#include "database.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    SAMPLE_USERS = 6
};

static const unsigned int SAMPLE_IDS[SAMPLE_USERS] = {123U, 456U, 789U, 321U, 654U, 987U};
static const char* SAMPLE_EMAILS[SAMPLE_USERS] = {"a@a.c", "m@z.x", "m@a.b", "b@c.d", "z@w.c", "a@a.a"};
static const char* SAMPLE_NAMES[SAMPLE_USERS] = {"name1", "name2", "name3", "name4", "name5", "name6"};
static const char* SAMPLE_PASSWORDS[SAMPLE_USERS] = {
    "password1", "password2", "password3", "password4", "password5", "password6"
};

int main(void) {
    Database* database = db_create();
    User* users[SAMPLE_USERS];

    for (int i = 0; i < SAMPLE_USERS; i++) {
        users[i] = user_create(SAMPLE_IDS[i], SAMPLE_EMAILS[i], SAMPLE_NAMES[i], SAMPLE_PASSWORDS[i]);
    }

    for (int i = 0; i < SAMPLE_USERS; i++) {
        db_insert(database, users[i]);
    }

    db_print_in_order_by_email(database);
    printf("\n");

    for (int i = 0; i < SAMPLE_USERS; i++) {
        User* user = db_query_by_email(database, users[i]->email);

        if (user != NULL) {
            printf("Found user: ");
            user_print(user);
        } else {
            printf("User not found\n");
        }
    }

    for (int i = 0; i < SAMPLE_USERS; i++) {
        db_remove_by_email(database, users[i]->email);
        db_print_in_order_by_email(database);
        printf("\n");
    }

    db_destroy(database);

    for (int i = 0; i < SAMPLE_USERS; i++) {
        user_destroy(users[i]);
    }

    return 0;
}
