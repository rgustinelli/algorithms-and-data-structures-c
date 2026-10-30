#include <stdio.h>

#include "heap_sort.h"

static void print_array(Element *array, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        element_print(array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    const int keys[] = {61, 73, 82, 28, 33, 57, 4, 15};
    const int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element array[size];

    element_make_array(array, keys, size);

    printf("Original array: ");
    print_array(array, size);

    heap_sort(array, size, NULL);

    printf("Sorted array (descending): ");
    print_array(array, size);

    return 0;
}
