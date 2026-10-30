/**
 * @file test_bst_uint.c
 * @brief Assert-based tests for the BST_UInt module (BST indexed by id).
 */
#include "bst_uint.h"
#include "user.h"

#include <assert.h>
#include <stdio.h>

static User* make_user(unsigned int id) {
    char email[32];
    snprintf(email, sizeof(email), "user%u@test.com", id);
    return user_create(id, email, "name", "pass");
}

static void test_empty_tree(void) {
    BST_UInt* bst = bst_uint_create();

    assert(bst_uint_size(bst) == 0);
    assert(bst_uint_query(bst, 1U) == NULL);

    /* Should not remove anything and must not crash on an empty tree. */
    bst_uint_remove(bst, 1U);
    assert(bst_uint_size(bst) == 0);

    bst_uint_destroy(bst);
}

static void test_single_element(void) {
    BST_UInt* bst = bst_uint_create();
    User* user = make_user(10U);

    bst_uint_insert(bst, user);

    assert(bst_uint_size(bst) == 1);
    assert(bst_uint_query(bst, 10U) == user);
    assert(bst_uint_query(bst, 99U) == NULL);

    bst_uint_destroy(bst);
    user_destroy(user);
}

static void test_insert_and_query_multiple(void) {
    BST_UInt* bst = bst_uint_create();
    unsigned int ids[] = {50U, 25U, 75U, 10U, 30U, 60U, 90U};
    const int count = (int) (sizeof(ids) / sizeof(ids[0]));
    User* users[7];

    for (int i = 0; i < count; i++) {
        users[i] = make_user(ids[i]);
        bst_uint_insert(bst, users[i]);
    }

    assert(bst_uint_size(bst) == count);

    for (int i = 0; i < count; i++) {
        assert(bst_uint_query(bst, ids[i]) == users[i]);
    }

    assert(bst_uint_query(bst, 999U) == NULL);

    bst_uint_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_duplicate_id_is_ignored(void) {
    /*
     * bst_uint_insert_recur() only recurses on cmp < 0 or cmp > 0; when a
     * key already exists (cmp == 0) the tree is left untouched and the new
     * user is not linked in. This test documents that existing behavior.
     */
    BST_UInt* bst = bst_uint_create();
    User* first = make_user(10U);
    User* second = make_user(10U);

    bst_uint_insert(bst, first);
    bst_uint_insert(bst, second);

    assert(bst_uint_size(bst) == 1);
    assert(bst_uint_query(bst, 10U) == first);

    bst_uint_destroy(bst);
    user_destroy(first);
    user_destroy(second);
}

static void test_remove_leaf(void) {
    BST_UInt* bst = bst_uint_create();
    User* root = make_user(50U);
    User* leaf = make_user(25U);

    bst_uint_insert(bst, root);
    bst_uint_insert(bst, leaf);

    bst_uint_remove(bst, 25U);

    assert(bst_uint_size(bst) == 1);
    assert(bst_uint_query(bst, 25U) == NULL);
    assert(bst_uint_query(bst, 50U) == root);

    bst_uint_destroy(bst);
    user_destroy(root);
    user_destroy(leaf);
}

static void test_remove_node_with_one_child(void) {
    BST_UInt* bst = bst_uint_create();
    User* root = make_user(50U);
    User* mid = make_user(25U);
    User* child = make_user(10U);

    bst_uint_insert(bst, root);
    bst_uint_insert(bst, mid);
    bst_uint_insert(bst, child);

    bst_uint_remove(bst, 25U);

    assert(bst_uint_size(bst) == 2);
    assert(bst_uint_query(bst, 25U) == NULL);
    assert(bst_uint_query(bst, 10U) == child);
    assert(bst_uint_query(bst, 50U) == root);

    bst_uint_destroy(bst);
    user_destroy(root);
    user_destroy(mid);
    user_destroy(child);
}

static void test_remove_node_with_two_children(void) {
    BST_UInt* bst = bst_uint_create();
    unsigned int ids[] = {50U, 25U, 75U, 60U, 90U};
    const int count = (int) (sizeof(ids) / sizeof(ids[0]));
    User* users[5];

    for (int i = 0; i < count; i++) {
        users[i] = make_user(ids[i]);
        bst_uint_insert(bst, users[i]);
    }

    /* 75 has two children (60 and 90); its in-order successor is 90. */
    bst_uint_remove(bst, 75U);

    assert(bst_uint_size(bst) == count - 1);
    assert(bst_uint_query(bst, 75U) == NULL);
    assert(bst_uint_query(bst, 60U) != NULL);
    assert(bst_uint_query(bst, 90U) != NULL);

    bst_uint_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_remove_root(void) {
    BST_UInt* bst = bst_uint_create();
    unsigned int ids[] = {50U, 25U, 75U};
    const int count = 3;
    User* users[3];

    for (int i = 0; i < count; i++) {
        users[i] = make_user(ids[i]);
        bst_uint_insert(bst, users[i]);
    }

    bst_uint_remove(bst, 50U);

    assert(bst_uint_size(bst) == count - 1);
    assert(bst_uint_query(bst, 50U) == NULL);
    assert(bst_uint_query(bst, 25U) != NULL);
    assert(bst_uint_query(bst, 75U) != NULL);

    bst_uint_destroy(bst);
    for (int i = 0; i < count; i++) {
        user_destroy(users[i]);
    }
}

static void test_remove_nonexistent_key(void) {
    BST_UInt* bst = bst_uint_create();
    User* user = make_user(10U);

    bst_uint_insert(bst, user);
    bst_uint_remove(bst, 999U);

    assert(bst_uint_size(bst) == 1);
    assert(bst_uint_query(bst, 10U) == user);

    bst_uint_destroy(bst);
    user_destroy(user);
}

static void test_print_functions_do_not_crash(void) {
    /*
     * The print functions write to stdout and have no return value, so
     * this is a smoke test: it only checks that they run without
     * crashing on both an empty and a populated tree.
     */
    BST_UInt* empty = bst_uint_create();
    bst_uint_print_in_order(empty);
    bst_uint_print_pre_order(empty);
    bst_uint_print_post_order(empty);
    bst_uint_destroy(empty);

    BST_UInt* bst = bst_uint_create();
    User* user = make_user(1U);
    bst_uint_insert(bst, user);
    bst_uint_print_in_order(bst);
    bst_uint_print_pre_order(bst);
    bst_uint_print_post_order(bst);
    bst_uint_destroy(bst);
    user_destroy(user);
}

int main(void) {
    test_empty_tree();
    test_single_element();
    test_insert_and_query_multiple();
    test_duplicate_id_is_ignored();
    test_remove_leaf();
    test_remove_node_with_one_child();
    test_remove_node_with_two_children();
    test_remove_root();
    test_remove_nonexistent_key();
    test_print_functions_do_not_crash();

    printf("test_bst_uint: all tests passed\n");
    return 0;
}
