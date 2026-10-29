/**
 * @file avl.h
 * @brief Public interface for the AVL tree implementation.
 */

#ifndef AVL_H
#define AVL_H

#include "element.h"

/**
 * @brief Represents a node in the AVL tree.
 */
typedef struct AVLNode {
    Element key;               /**< Stored element. */
    struct AVLNode *left;      /**< Pointer to the left child. */
    struct AVLNode *right;     /**< Pointer to the right child. */
    int height;                /**< Height of the subtree rooted at this node. */
} AVLNode;

/**
 * @brief Inserts a new element into the AVL tree.
 *
 * @param root Pointer to the root node.
 * @param key Element to insert.
 *
 * @return Updated root of the AVL tree.
 */
AVLNode *avl_insert(AVLNode *root, Element key);

/**
 * @brief Removes an element from the AVL tree.
 *
 * @param root Pointer to the root node.
 * @param key Element to remove.
 *
 * @return Updated root of the AVL tree.
 */
AVLNode *avl_remove(AVLNode *root, Element key);

/**
 * @brief Searches for an element in the AVL tree.
 *
 * @param root Pointer to the root node.
 * @param key Element to search for.
 *
 * @return Pointer to the node if found, otherwise NULL.
 */
AVLNode *avl_search(AVLNode *root, Element key);

/**
 * @brief Prints the tree using an in-order traversal.
 *
 * @param root Pointer to the root node.
 */
void avl_inorder(const AVLNode *root);

/**
 * @brief Prints the tree using a pre-order traversal.
 *
 * @param root Pointer to the root node.
 */
void avl_preorder(const AVLNode *root);

/**
 * @brief Prints the tree using a post-order traversal.
 *
 * @param root Pointer to the root node.
 */
void avl_postorder(const AVLNode *root);

/**
 * @brief Releases all memory allocated by the AVL tree.
 *
 * @param root Pointer to the root node.
 */
void avl_destroy(AVLNode *root);

#endif /* AVL_H */
