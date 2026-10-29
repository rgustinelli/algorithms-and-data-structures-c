#include <stdio.h>

#include "avl.h"

int main(void) {
    AVLNode *tree = NULL;

    printf("=== AVL INSERT TEST ===\n");

    int values[] = {
        30,
        20,
        10,
        25,
        40,
        50,
        60,
        5
    };

    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        tree = avl_insert(tree, values[i]);
    }

    printf("\nInorder traversal:\n");
    avl_inorder(tree);

    printf("\n\nPreorder traversal:\n");
    avl_preorder(tree);

    printf("\n\nPostorder traversal:\n");
    avl_postorder(tree);

    printf("\n\n=== AVL SEARCH TEST ===\n");

    int search_values[] = {
        25,
        100
    };

    for (int i = 0; i < 2; i++) {
        if (avl_search(tree, search_values[i]) != NULL) {
            printf("Key %d found\n", search_values[i]);
        }
        else {
            printf("Key %d not found\n", search_values[i]);
        }
    }

    printf("\n=== AVL REMOVE TEST ===\n");

    printf("\nRemoving leaf node (5):\n");
    tree = avl_remove(tree, 5);
    avl_inorder(tree);

    printf("\n\nRemoving node with one child (60):\n");
    tree = avl_remove(tree, 60);
    avl_inorder(tree);

    printf("\n\nRemoving node with two children (30):\n");
    tree = avl_remove(tree, 30);
    avl_inorder(tree);

    printf("\n\nFinal preorder:\n");
    avl_preorder(tree);

    printf("\n\n=== AVL DESTROY TEST ===\n");
    avl_destroy(tree);
    printf("Tree destroyed successfully\n");

    return 0;
}
