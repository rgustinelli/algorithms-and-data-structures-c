#include <stddef.h>

#include "heap_sort.h"

/**
 * Restores the min-heap property for the subtree rooted at index i.
 *
 * Compares data[i] with its two children (by key, via element_compare)
 * and, if either child is smaller, swaps it into place and recurses
 * into the affected subtree.
 *
 * @param data Array representing the heap.
 * @param size Number of elements considered part of the heap.
 * @param i    Index of the subtree root to sift down.
 */
static void heapify(Element *data, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && element_compare(data[left], data[smallest]) < 0) {
        smallest = left;
    }

    if (right < size && element_compare(data[right], data[smallest]) < 0) {
        smallest = right;
    }

    if (smallest != i) {
        Element temp = data[i];
        data[i] = data[smallest];
        data[smallest] = temp;

        heapify(data, size, smallest);
    }
}

void heap_sort(Element *data, int size, void (*on_step)(Element *, int, int)) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(data, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        Element temp = data[0];
        data[0] = data[i];
        data[i] = temp;

        heapify(data, i, 0);

        if (on_step != NULL) {
            on_step(data, size, i);
        }
    }
}
