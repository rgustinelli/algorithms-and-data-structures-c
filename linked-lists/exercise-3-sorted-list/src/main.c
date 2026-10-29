#include "sorted_list.h"

int main(void) {
    SortedList* list = slist_create();

    slist_insert(list, 456, "Bob", 7.0);
    slist_insert(list, 789, "Charlie", 8.0);
    slist_insert(list, 123, "Alice", 9.5);

    slist_print(list);

    slist_destroy(list);

    return 0;
}
