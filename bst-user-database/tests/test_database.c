/**
 * @file test_database.c
 * @brief Assert-based tests for the Database module (dual email/id index).
 */
#include "database.h"
#include "user.h"

#include <assert.h>
#include <stdio.h>

static void test_empty_database(void) {
    Database* db = db_create();

    assert(db_size(db) == 0);
    assert(db_query_by_email(db, "missing@test.com") == NULL);
    assert(db_query_by_id(db, 1U) == NULL);

    /* Removing from an empty database must be a safe no-op. */
    db_remove_by_email(db, "missing@test.com");
    db_remove_by_id(db, 1U);
    assert(db_size(db) == 0);

    db_destroy(db);
}

static void test_insert_indexes_both_email_and_id(void) {
    Database* db = db_create();
    User* user = user_create(10U, "a@test.com", "Alice", "pw");

    db_insert(db, user);

    assert(db_size(db) == 1);
    assert(db_query_by_email(db, "a@test.com") == user);
    assert(db_query_by_id(db, 10U) == user);

    db_destroy(db);
    user_destroy(user);
}

static void test_query_unknown_keys(void) {
    Database* db = db_create();
    User* user = user_create(10U, "a@test.com", "Alice", "pw");

    db_insert(db, user);

    assert(db_query_by_email(db, "unknown@test.com") == NULL);
    assert(db_query_by_id(db, 999U) == NULL);

    db_destroy(db);
    user_destroy(user);
}

static void test_remove_by_email_updates_both_indexes(void) {
    Database* db = db_create();
    User* user = user_create(10U, "a@test.com", "Alice", "pw");

    db_insert(db, user);
    db_remove_by_email(db, "a@test.com");

    assert(db_size(db) == 0);
    assert(db_query_by_email(db, "a@test.com") == NULL);
    assert(db_query_by_id(db, 10U) == NULL);

    db_destroy(db);
    user_destroy(user);
}

static void test_remove_by_id_updates_both_indexes(void) {
    Database* db = db_create();
    User* user = user_create(10U, "a@test.com", "Alice", "pw");

    db_insert(db, user);
    db_remove_by_id(db, 10U);

    assert(db_size(db) == 0);
    assert(db_query_by_email(db, "a@test.com") == NULL);
    assert(db_query_by_id(db, 10U) == NULL);

    db_destroy(db);
    user_destroy(user);
}

static void test_remove_nonexistent_is_noop(void) {
    Database* db = db_create();
    User* user = user_create(10U, "a@test.com", "Alice", "pw");

    db_insert(db, user);
    db_remove_by_email(db, "missing@test.com");
    db_remove_by_id(db, 999U);

    assert(db_size(db) == 1);
    assert(db_query_by_email(db, "a@test.com") == user);
    assert(db_query_by_id(db, 10U) == user);

    db_destroy(db);
    user_destroy(user);
}

static void test_multiple_users(void) {
    Database* db = db_create();
    unsigned int ids[] = {30U, 10U, 20U};
    const char* emails[] = {"c@test.com", "a@test.com", "b@test.com"};
    const int count = 3;
    User* users[3];

    for (int i = 0; i < count; i++) {
        users[i] = user_create(ids[i], emails[i], "name", "pw");
        db_insert(db, users[i]);
    }

    assert(db_size(db) == count);

    for (int i = 0; i < count; i++) {
        assert(db_query_by_id(db, ids[i]) == users[i]);
        assert(db_query_by_email(db, emails[i]) == users[i]);
    }

    db_remove_by_id(db, 10U);
    assert(db_size(db) == count - 1);
    assert(db_query_by_email(db, "a@test.com") == NULL);

    db_destroy(db);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_print_functions_do_not_crash(void) {
    Database* db = db_create();
    User* user = user_create(1U, "a@test.com", "Alice", "pw");

    db_insert(db, user);

    db_print_in_order_by_email(db);
    db_print_pre_order_by_email(db);
    db_print_post_order_by_email(db);
    db_print_in_order_by_id(db);
    db_print_pre_order_by_id(db);
    db_print_post_order_by_id(db);

    db_destroy(db);
    user_destroy(user);
}

int main(void) {
    test_empty_database();
    test_insert_indexes_both_email_and_id();
    test_query_unknown_keys();
    test_remove_by_email_updates_both_indexes();
    test_remove_by_id_updates_both_indexes();
    test_remove_nonexistent_is_noop();
    test_multiple_users();
    test_print_functions_do_not_crash();

    printf("test_database: all tests passed\n");
    return 0;
}
