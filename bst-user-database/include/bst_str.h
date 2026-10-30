/**
 * Binary Search Tree implementation for string-indexed user records.
 */
#ifndef BST_STR_H
#define BST_STR_H

#include "user.h"

typedef struct BST_Str BST_Str;

BST_Str* bst_str_create(void);
void bst_str_destroy(BST_Str* bst);

User* bst_str_query(BST_Str* bst, const char* key);
void bst_str_insert(BST_Str* bst, User* user);
void bst_str_remove(BST_Str* bst, const char* key);

int bst_str_size(BST_Str* bst);
void bst_str_print_pre_order(BST_Str* bst);
void bst_str_print_in_order(BST_Str* bst);
void bst_str_print_post_order(BST_Str* bst);

#endif
