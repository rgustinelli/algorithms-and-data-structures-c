/**
 * @file test_avl.c
 * @brief Automated tests for the AVL tree implementation.
 *
 * These tests use plain assert() checks instead of an external framework,
 * to keep the project dependency-free. Each test focuses on one behavior
 * of the public API declared in avl.h.
 */

#include "avl.h"

#include <assert.h>
#include <stdio.h>

/* Returns 1 if the subtree rooted at node respects the AVL balance
 * invariant (|height(left) - height(right)| <= 1 at every node),
 * otherwise 0. Used to confirm the tree stays balanced after
 * insertions and removals. */
static int height_of(const AVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    int left_height = height_of(node->left);
    int right_height = height_of(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

static int is_balanced(const AVLNode *node) {
    if (node == NULL) {
        return 1;
    }

    int balance = height_of(node->left) - height_of(node->right);

    if (balance > 1 || balance < -1) {
        return 0;
    }

    return is_balanced(node->left) && is_balanced(node->right);
}

/* Empty tree: search must return NULL, remove must be a safe no-op. */
static void test_empty_tree(void) {
    AVLNode *tree = NULL;

    assert(avl_search(tree, 10) == NULL);

    tree = avl_remove(tree, 10);
    assert(tree == NULL);

    avl_destroy(tree);
    printf("test_empty_tree: OK\n");
}

/* Single element: insert, find it, then remove it back to an empty tree. */
static void test_single_element(void) {
    AVLNode *tree = NULL;

    tree = avl_insert(tree, 42);
    assert(tree != NULL);
    assert(avl_search(tree, 42) != NULL);
    assert(tree->key == 42);

    tree = avl_remove(tree, 42);
    assert(tree == NULL);

    avl_destroy(tree);
    printf("test_single_element: OK\n");
}

/* Inserting a value that already exists must not create a duplicate
 * node or corrupt the tree. */
static void test_duplicate_insertion(void) {
    AVLNode *tree = NULL;

    tree = avl_insert(tree, 10);
    tree = avl_insert(tree, 10);
    tree = avl_insert(tree, 10);

    assert(tree != NULL);
    assert(tree->left == NULL);
    assert(tree->right == NULL);
    assert(avl_search(tree, 10) != NULL);

    avl_destroy(tree);
    printf("test_duplicate_insertion: OK\n");
}

/* Inserting values in increasing order is the classic case that forces
 * rotations in a plain BST. The tree must remain balanced afterward. */
static void test_insert_keeps_balance(void) {
    AVLNode *tree = NULL;
    int i;

    for (i = 1; i <= 100; i++) {
        tree = avl_insert(tree, i);
    }

    assert(is_balanced(tree));

    for (i = 1; i <= 100; i++) {
        assert(avl_search(tree, i) != NULL);
    }
    assert(avl_search(tree, 0) == NULL);
    assert(avl_search(tree, 101) == NULL);

    avl_destroy(tree);
    printf("test_insert_keeps_balance: OK\n");
}

/* Covers the three removal cases (leaf, one child, two children) and
 * the specific case of removing the root, then checks the tree stays
 * balanced and consistent. */
static void test_remove_cases(void) {
    AVLNode *tree = NULL;
    int values[] = {30, 20, 10, 25, 40, 50, 60, 5};
    size_t size = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < size; i++) {
        tree = avl_insert(tree, values[i]);
    }

    /* Remove a leaf node. */
    tree = avl_remove(tree, 5);
    assert(avl_search(tree, 5) == NULL);
    assert(is_balanced(tree));

    /* Remove a node with a single child. */
    tree = avl_remove(tree, 60);
    assert(avl_search(tree, 60) == NULL);
    assert(is_balanced(tree));

    /* Remove the root, which has two children. */
    int old_root_key = tree->key;
    tree = avl_remove(tree, old_root_key);
    assert(avl_search(tree, old_root_key) == NULL);
    assert(is_balanced(tree));

    /* Every remaining value must still be reachable. */
    assert(avl_search(tree, 10) != NULL);
    assert(avl_search(tree, 20) != NULL);
    assert(avl_search(tree, 25) != NULL);
    assert(avl_search(tree, 40) != NULL);
    assert(avl_search(tree, 50) != NULL);

    avl_destroy(tree);
    printf("test_remove_cases: OK\n");
}

/* Removing a value that is not present must leave the tree unchanged. */
static void test_remove_nonexistent(void) {
    AVLNode *tree = NULL;
    int values[] = {10, 5, 15};
    size_t size = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < size; i++) {
        tree = avl_insert(tree, values[i]);
    }

    tree = avl_remove(tree, 999);

    assert(avl_search(tree, 10) != NULL);
    assert(avl_search(tree, 5) != NULL);
    assert(avl_search(tree, 15) != NULL);
    assert(is_balanced(tree));

    avl_destroy(tree);
    printf("test_remove_nonexistent: OK\n");
}

/* Extreme values (INT-range boundaries) must be handled like any
 * other key, since comparisons go through element_compare(). */
static void test_extreme_values(void) {
    AVLNode *tree = NULL;

    tree = avl_insert(tree, -1000000);
    tree = avl_insert(tree, 1000000);
    tree = avl_insert(tree, 0);

    assert(avl_search(tree, -1000000) != NULL);
    assert(avl_search(tree, 1000000) != NULL);
    assert(avl_search(tree, 0) != NULL);
    assert(is_balanced(tree));

    avl_destroy(tree);
    printf("test_extreme_values: OK\n");
}

int main(void) {
    test_empty_tree();
    test_single_element();
    test_duplicate_insertion();
    test_insert_keeps_balance();
    test_remove_cases();
    test_remove_nonexistent();
    test_extreme_values();

    printf("\nAll tests passed.\n");
    return 0;
}
