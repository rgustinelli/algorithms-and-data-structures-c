/**
 * @file bst_uint.c
 * @brief Binary search tree implementation indexed by User::id.
 */
#include "bst_uint.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Each node stores a pointer to a user record as payload.
 */
typedef struct Node {
    User* user;
    struct Node* left;
    struct Node* right;
} Node;

struct BST_UInt {
    Node* root;
};

/**
 * Compares two unsigned ids using BST ordering semantics.
 * @param lhs Left-hand id.
 * @param rhs Right-hand id.
 * @return -1 if lhs < rhs, 1 if lhs > rhs, otherwise 0.
 */
static int compare_ids(unsigned int lhs, unsigned int rhs) {
    if (lhs < rhs) {
        return -1;
    }

    if (lhs > rhs) {
        return 1;
    }

    return 0;
}

/**
 * Allocates and initializes a new node for the given user.
 * @param user User stored in the node.
 * @return Pointer to the newly allocated node.
 */
static Node* create_node(User* user) {
    Node* new_node = malloc(sizeof(Node));

    new_node->user = user;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * Recursively frees all nodes in a subtree.
 * @param node Root of the subtree to free.
 * @return None.
 */
static void bst_uint_destroy_recur(Node* node) {
    if (node == NULL) {
        return;
    }

    bst_uint_destroy_recur(node->left);
    bst_uint_destroy_recur(node->right);
    free(node);
}

/**
 * Recursively counts nodes in a subtree.
 * @param node Root of the subtree.
 * @return Number of nodes in the subtree.
 */
static int bst_uint_size_recur(Node* node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + bst_uint_size_recur(node->left) + bst_uint_size_recur(node->right);
}

/**
 * Recursively searches for a user by id key.
 * @param node Current subtree root.
 * @param key Id key to search for.
 * @return Pointer to the matching user, or NULL if not found.
 */
static User* bst_uint_search_recur(Node* node, unsigned int key) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = compare_ids(key, node->user->id);

    if (cmp == 0) {
        return node->user;
    }

    if (cmp < 0) {
        return bst_uint_search_recur(node->left, key);
    }

    return bst_uint_search_recur(node->right, key);
}

/**
 * Recursively inserts a user while preserving BST ordering by id.
 * @param node Current subtree root.
 * @param user User to insert.
 * @return New root of the subtree after insertion.
 */
static Node* bst_uint_insert_recur(Node* node, User* user) {
    if (node == NULL) {
        return create_node(user);
    }

    int cmp = compare_ids(user->id, node->user->id);

    if (cmp < 0) {
        node->left = bst_uint_insert_recur(node->left, user);
    } else if (cmp > 0) {
        node->right = bst_uint_insert_recur(node->right, user);
    }

    return node;
}

/**
 * Returns the in-order successor node of a node with two children.
 * @param node Node whose successor is needed.
 * @return Left-most node in the right subtree.
 */
static Node* bst_uint_successor(Node* node) {
    Node* cur = node->right;

    while (cur->left != NULL) {
        cur = cur->left;
    }

    return cur;
}

/**
 * Recursively removes a node by id and returns the new subtree root.
 * @param node Current subtree root.
 * @param key Id key to remove.
 * @return New root of the subtree after removal.
 */
static Node* bst_uint_remove_recur(Node* node, unsigned int key) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = compare_ids(key, node->user->id);

    if (cmp < 0) {
        node->left = bst_uint_remove_recur(node->left, key);
    } else if (cmp > 0) {
        node->right = bst_uint_remove_recur(node->right, key);
    } else {
        if (node->left == NULL) {
            Node* trash = node;

            node = node->right;
            free(trash);
        } else if (node->right == NULL) {
            Node* trash = node;

            node = node->left;
            free(trash);
        } else {
            Node* temp = bst_uint_successor(node);

            node->user = temp->user;
            node->right = bst_uint_remove_recur(node->right, temp->user->id);
        }
    }

    return node;
}

/**
 * Prints users from subtree in-order.
 * @param node Root of the subtree to print.
 * @return None.
 */
static void bst_uint_print_in_order_recur(Node* node) {
    if (node == NULL) {
        return;
    }

    bst_uint_print_in_order_recur(node->left);
    user_print(node->user);
    bst_uint_print_in_order_recur(node->right);
}

/**
 * Prints users from subtree pre-order.
 * @param node Root of the subtree to print.
 * @return None.
 */
static void bst_uint_print_pre_order_recur(Node* node) {
    if (node == NULL) {
        return;
    }

    user_print(node->user);
    bst_uint_print_pre_order_recur(node->left);
    bst_uint_print_pre_order_recur(node->right);
}

/**
 * Prints users from subtree post-order.
 * @param node Root of the subtree to print.
 * @return None.
 */
static void bst_uint_print_post_order_recur(Node* node) {
    if (node == NULL) {
        return;
    }

    bst_uint_print_post_order_recur(node->left);
    bst_uint_print_post_order_recur(node->right);
    user_print(node->user);
}

/**
 * Creates an empty BST indexed by user id.
 * @param None.
 * @return Pointer to a newly created empty BST.
 */
BST_UInt* bst_uint_create(void) {
    BST_UInt* bst = malloc(sizeof(BST_UInt));

    bst->root = NULL;

    return bst;
}

/**
 * Destroys BST nodes (stored users are not freed).
 * @param bst BST instance to destroy.
 * @return None.
 */
void bst_uint_destroy(BST_UInt* bst) {
    bst_uint_destroy_recur(bst->root);
    free(bst);
}

/**
 * Returns the user matching id, or NULL when not found.
 * @param bst BST instance to query.
 * @param key Id key to search for.
 * @return Pointer to the matching user, or NULL.
 */
User* bst_uint_query(BST_UInt* bst, unsigned int key) {
    return bst_uint_search_recur(bst->root, key);
}

/**
 * Inserts a user using user->id as key.
 * @param bst BST instance to modify.
 * @param user User to insert.
 * @return None.
 */
void bst_uint_insert(BST_UInt* bst, User* user) {
    bst->root = bst_uint_insert_recur(bst->root, user);
}

/**
 * Removes the node with the given id if present.
 * @param bst BST instance to modify.
 * @param key Id key to remove.
 * @return None.
 */
void bst_uint_remove(BST_UInt* bst, unsigned int key) {
    bst->root = bst_uint_remove_recur(bst->root, key);
}

/**
 * Returns the number of nodes in the BST.
 * @param bst BST instance to inspect.
 * @return Number of nodes currently stored.
 */
int bst_uint_size(BST_UInt* bst) {
    return bst_uint_size_recur(bst->root);
}

/**
 * Prints users in-order by id.
 * @param bst BST instance to print.
 * @return None.
 */
void bst_uint_print_in_order(BST_UInt* bst) {
    if (bst->root != NULL) {
        printf("Id, Email, Name, Password\n");
        bst_uint_print_in_order_recur(bst->root);
    } else {
        printf("Empty database\n");
    }
}

/**
 * Prints users in pre-order by id.
 * @param bst BST instance to print.
 * @return None.
 */
void bst_uint_print_pre_order(BST_UInt* bst) {
    if (bst->root != NULL) {
        printf("Id, Email, Name, Password\n");
        bst_uint_print_pre_order_recur(bst->root);
    } else {
        printf("Empty database\n");
    }
}

/**
 * Prints users in post-order by id.
 * @param bst BST instance to print.
 * @return None.
 */
void bst_uint_print_post_order(BST_UInt* bst) {
    if (bst->root != NULL) {
        printf("Id, Email, Name, Password\n");
        bst_uint_print_post_order_recur(bst->root);
    } else {
        printf("Empty database\n");
    }
}
