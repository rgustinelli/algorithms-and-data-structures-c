/**
 * Binary Search Tree implementation for unsigned integer-indexed user records.
 */
#ifndef BST_UINT_H
#define BST_UINT_H

#include "user.h"

typedef struct BST_UInt BST_UInt;

BST_UInt* bst_uint_create(void);
void bst_uint_destroy(BST_UInt* bst);

User* bst_uint_query(BST_UInt* bst, unsigned int key);
void bst_uint_insert(BST_UInt* bst, User* user);
void bst_uint_remove(BST_UInt* bst, unsigned int key);

int bst_uint_size(BST_UInt* bst);
void bst_uint_print_pre_order(BST_UInt* bst);
void bst_uint_print_in_order(BST_UInt* bst);
void bst_uint_print_post_order(BST_UInt* bst);

#endif
