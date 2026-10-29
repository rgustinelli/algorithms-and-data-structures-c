#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Returns the greater of two integers. */
static int avl_max(int a, int b) {
    return (a > b) ? a : b;
}

/* Returns the height of a node. A NULL node has height 0. */
static int avl_height(const AVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

/* Creates and initializes a new AVL node. */
static AVLNode *avl_create_node(Element key) {
    AVLNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

/* Returns the balance factor of a node. */
static int avl_balance_factor(const AVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    return avl_height(node->left) - avl_height(node->right);
}

/* Performs a right rotation on the subtree rooted at y. */
static AVLNode *avl_right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;

    /* Perform rotation. */
    x->right = y;
    y->left = t2;

    /* Update heights. */
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;

    return x;
}

/* Performs a left rotation on the subtree rooted at x. */
static AVLNode *avl_left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;

    /* Perform rotation. */
    y->left = x;
    x->right = t2;

    /* Update heights. */
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;

    return y;
}

/* Inserts a key into the AVL tree. */
AVLNode *avl_insert(AVLNode *root, Element key) {
    if (root == NULL) {
        return avl_create_node(key);
    }

    if (element_compare(key, root->key) < 0) {
        root->left = avl_insert(root->left, key);
    }
    else if (element_compare(key, root->key) > 0) {
        root->right = avl_insert(root->right, key);
    }
    else {
        return root;
    }

    /* Update height. */
    root->height = avl_max(
        avl_height(root->left),
        avl_height(root->right)
    ) + 1;

    /* Check balance factor. */
    int balance = avl_balance_factor(root);

    /* Left Left case. */
    if (balance > 1 && element_compare(key, root->left->key) < 0) {
        return avl_right_rotate(root);
    }

    /* Right Right case. */
    if (balance < -1 && element_compare(key, root->right->key) > 0) {
        return avl_left_rotate(root);
    }

    /* Left Right case. */
    if (balance > 1 && element_compare(key, root->left->key) > 0) {
        root->left = avl_left_rotate(root->left);
        return avl_right_rotate(root);
    }

    /* Right Left case. */
    if (balance < -1 && element_compare(key, root->right->key) < 0) {
        root->right = avl_right_rotate(root->right);
        return avl_left_rotate(root);
    }

    return root;
}

/* Searches for a key in the AVL tree. */
AVLNode *avl_search(AVLNode *root, Element key) {
    if (root == NULL) {
        return NULL;
    }

    if (element_compare(key, root->key) == 0) {
        return root;
    }

    if (element_compare(key, root->key) < 0) {
        return avl_search(root->left, key);
    }

    return avl_search(root->right, key);
}

/* Returns the node with the smallest key in a subtree. */
static AVLNode *avl_min_value_node(AVLNode *node) {
    AVLNode *current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

/* Removes a key from the AVL tree. */
AVLNode *avl_remove(AVLNode *root, Element key) {
    if (root == NULL) {
        return NULL;
    }

    /* Search for the node to remove. */
    if (element_compare(key, root->key) < 0) {
        root->left = avl_remove(root->left, key);
    }
    else if (element_compare(key, root->key) > 0) {
        root->right = avl_remove(root->right, key);
    }
    else {
        /* Node with one child or no child. */
        if (root->left == NULL || root->right == NULL) {
            AVLNode *temp;

            if (root->left != NULL) {
                temp = root->left;
            }
            else {
                temp = root->right;
            }

            /* No child. */
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                /* One child. */
                *root = *temp;
            }

            free(temp);
        }
        /* Node with two children. */
        else {
            AVLNode *temp = avl_min_value_node(root->right);

            root->key = temp->key;
            root->right = avl_remove(root->right, temp->key);
        }
    }

    /* Tree had only one node. */
    if (root == NULL) {
        return NULL;
    }

    /* Update height. */
    root->height = avl_max(
        avl_height(root->left),
        avl_height(root->right)
    ) + 1;

    /* Check balance factor. */
    int balance = avl_balance_factor(root);

    /* Left Left case. */
    if (balance > 1 && avl_balance_factor(root->left) >= 0) {
        return avl_right_rotate(root);
    }

    /* Left Right case. */
    if (balance > 1 && avl_balance_factor(root->left) < 0) {
        root->left = avl_left_rotate(root->left);
        return avl_right_rotate(root);
    }

    /* Right Right case. */
    if (balance < -1 && avl_balance_factor(root->right) <= 0) {
        return avl_left_rotate(root);
    }

    /* Right Left case. */
    if (balance < -1 && avl_balance_factor(root->right) > 0) {
        root->right = avl_right_rotate(root->right);
        return avl_left_rotate(root);
    }

    return root;
}

/* Performs an inorder traversal of the AVL tree. */
void avl_inorder(const AVLNode *root) {
    if (root == NULL) {
        return;
    }

    avl_inorder(root->left);
    element_print(root->key);
    printf(" ");
    avl_inorder(root->right);
}

/* Performs a preorder traversal of the AVL tree. */
void avl_preorder(const AVLNode *root) {
    if (root == NULL) {
        return;
    }

    element_print(root->key);
    printf(" ");
    avl_preorder(root->left);
    avl_preorder(root->right);
}

/* Performs a postorder traversal of the AVL tree. */
void avl_postorder(const AVLNode *root) {
    if (root == NULL) {
        return;
    }

    avl_postorder(root->left);
    avl_postorder(root->right);
    element_print(root->key);
    printf(" ");
}

/* Frees all nodes of the AVL tree. */
void avl_destroy(AVLNode *root) {
    if (root == NULL) {
        return;
    }

    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root);
}
