/**
 * @file test_bst_str.c
 * @brief Assert-based tests for the BST_Str module (BST indexed by email).
 */
#include "bst_str.h"
#include "user.h"

#include <assert.h>
#include <stdio.h>

static User* make_user(unsigned int id, const char* email) {
    return user_create(id, email, "name", "pass");
}

static void test_empty_tree(void) {
    BST_Str* bst = bst_str_create();

    assert(bst_str_size(bst) == 0);
    assert(bst_str_query(bst, "missing@test.com") == NULL);

    bst_str_remove(bst, "missing@test.com");
    assert(bst_str_size(bst) == 0);

    bst_str_destroy(bst);
}

static void test_single_element(void) {
    BST_Str* bst = bst_str_create();
    User* user = make_user(1U, "m@test.com");

    bst_str_insert(bst, user);

    assert(bst_str_size(bst) == 1);
    assert(bst_str_query(bst, "m@test.com") == user);
    assert(bst_str_query(bst, "other@test.com") == NULL);

    bst_str_destroy(bst);
    user_destroy(user);
}

static void test_insert_and_query_multiple(void) {
    BST_Str* bst = bst_str_create();
    const char* emails[] = {"m@test.com", "b@test.com", "z@test.com", "a@test.com", "c@test.com"};
    const int count = (int) (sizeof(emails) / sizeof(emails[0]));
    User* users[5];

    for (int i = 0; i < count; i++) {
        users[i] = make_user((unsigned int) i, emails[i]);
        bst_str_insert(bst, users[i]);
    }

    assert(bst_str_size(bst) == count);

    for (int i = 0; i < count; i++) {
        assert(bst_str_query(bst, emails[i]) == users[i]);
    }

    assert(bst_str_query(bst, "unknown@test.com") == NULL);

    bst_str_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_duplicate_email_is_ignored(void) {
    /*
     * As with BST_UInt, bst_str_insert_recur() leaves the tree unchanged
     * when the key (email) already exists. Documented here rather than
     * changed, since altering this behavior would change the module's
     * original semantics.
     */
    BST_Str* bst = bst_str_create();
    User* first = make_user(1U, "dup@test.com");
    User* second = make_user(2U, "dup@test.com");

    bst_str_insert(bst, first);
    bst_str_insert(bst, second);

    assert(bst_str_size(bst) == 1);
    assert(bst_str_query(bst, "dup@test.com") == first);

    bst_str_destroy(bst);
    user_destroy(first);
    user_destroy(second);
}

static void test_remove_leaf(void) {
    BST_Str* bst = bst_str_create();
    User* root = make_user(1U, "m@test.com");
    User* leaf = make_user(2U, "b@test.com");

    bst_str_insert(bst, root);
    bst_str_insert(bst, leaf);

    bst_str_remove(bst, "b@test.com");

    assert(bst_str_size(bst) == 1);
    assert(bst_str_query(bst, "b@test.com") == NULL);
    assert(bst_str_query(bst, "m@test.com") == root);

    bst_str_destroy(bst);
    user_destroy(root);
    user_destroy(leaf);
}

static void test_remove_node_with_two_children(void) {
    BST_Str* bst = bst_str_create();
    const char* emails[] = {"m@test.com", "b@test.com", "z@test.com", "y@test.com", "zz@test.com"};
    const int count = (int) (sizeof(emails) / sizeof(emails[0]));
    User* users[5];

    for (int i = 0; i < count; i++) {
        users[i] = make_user((unsigned int) i, emails[i]);
        bst_str_insert(bst, users[i]);
    }

    /* "z@test.com" has two children ("y@test.com" and "zz@test.com"). */
    bst_str_remove(bst, "z@test.com");

    assert(bst_str_size(bst) == count - 1);
    assert(bst_str_query(bst, "z@test.com") == NULL);
    assert(bst_str_query(bst, "y@test.com") != NULL);
    assert(bst_str_query(bst, "zz@test.com") != NULL);

    bst_str_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_remove_root(void) {
    BST_Str* bst = bst_str_create();
    const char* emails[] = {"m@test.com", "b@test.com", "z@test.com"};
    const int count = 3;
    User* users[3];

    for (int i = 0; i < count; i++) {
        users[i] = make_user((unsigned int) i, emails[i]);
        bst_str_insert(bst, users[i]);
    }

    bst_str_remove(bst, "m@test.com");

    assert(bst_str_size(bst) == count - 1);
    assert(bst_str_query(bst, "m@test.com") == NULL);
    assert(bst_str_query(bst, "b@test.com") != NULL);
    assert(bst_str_query(bst, "z@test.com") != NULL);

    bst_str_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_remove_nonexistent_key(void) {
    BST_Str* bst = bst_str_create();
    User* user = make_user(1U, "m@test.com");

    bst_str_insert(bst, user);
    bst_str_remove(bst, "missing@test.com");

    assert(bst_str_size(bst) == 1);
    assert(bst_str_query(bst, "m@test.com") == user);

    bst_str_destroy(bst);
    user_destroy(user);
}

static void test_print_functions_do_not_crash(void) {
    BST_Str* empty = bst_str_create();
    bst_str_print_in_order(empty);
    bst_str_print_pre_order(empty);
    bst_str_print_post_order(empty);
    bst_str_destroy(empty);

    BST_Str* bst = bst_str_create();
    User* user = make_user(1U, "m@test.com");
    bst_str_insert(bst, user);
    bst_str_print_in_order(bst);
    bst_str_print_pre_order(bst);
    bst_str_print_post_order(bst);
    bst_str_destroy(bst);
    user_destroy(user);
}

int main(void) {
    test_empty_tree();
    test_single_element();
    test_insert_and_query_multiple();
    test_duplicate_email_is_ignored();
    test_remove_leaf();
    test_remove_node_with_two_children();
    test_remove_root();
    test_remove_nonexistent_key();
    test_print_functions_do_not_crash();

    printf("test_bst_str: all tests passed\n");
    return 0;
}
