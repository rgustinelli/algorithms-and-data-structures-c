#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    LinkedList* list = list_create();

    printf("Inserting elements: 10, 20, 30, 40, 50\n");
    list_insert_last(list, 10);
    list_insert_last(list, 20);
    list_insert_last(list, 30);
    list_insert_last(list, 40);
    list_insert_last(list, 50);

    printf("List after insertions: ");
    list_print(list);

    printf("List size: %zu\n", list_size(list));
    printf("Is empty: %s\n", list_is_empty(list) ? "true" : "false");

    printf("\nGetting element at position 2: %d\n", list_get_at(list, 2));

    printf("\nInserting 25 at position 2:\n");
    list_insert_at(list, 2, 25);
    printf("List after insert_at: ");
    list_print(list);

    printf("\nInserting 5 at first position:\n");
    list_insert_first(list, 5);
    printf("List after insert_first: ");
    list_print(list);

    printf("\nRemoving first element:\n");
    list_remove_first(list);
    printf("List after remove_first: ");
    list_print(list);

    printf("\nRemoving last element:\n");
    list_remove_last(list);
    printf("List after remove_last: ");
    list_print(list);

    printf("\nRemoving element at position 2:\n");
    list_remove_at(list, 2);
    printf("List after remove_at: ");
    list_print(list);

    printf("\nFinal list size: %zu\n", list_size(list));

    list_destroy(list);

    return 0;
}
