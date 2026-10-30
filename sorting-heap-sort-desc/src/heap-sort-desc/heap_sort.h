#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "../shared/element.h"

/**
 * Sorts an array of Element in descending order (by key) using heap sort.
 *
 * The implementation builds a min-heap over the input and repeatedly
 * extracts the element with the smallest key to the end of the array.
 * As a result, the array ends up sorted in descending order (largest
 * key first), unlike the textbook heap sort (which uses a max-heap to
 * produce ascending order).
 *
 * @param data    Array of Element to sort in place.
 * @param size    Number of elements in the array. Passing 0 is safe
 *                and leaves the array untouched.
 * @param on_step Optional callback invoked right after each element is
 *                placed in its final position. Receives the array, its
 *                total size, and the index of the element just placed.
 *                Pass NULL if no callback is needed.
 *
 * @note Time complexity: O(n log n) in the best, average, and worst
 *       case (heap sort does not have a linear best case, unlike
 *       insertion sort).
 * @note Space complexity: O(log n) auxiliary, due to the recursive
 *       implementation of the sift-down step (heapify).
 */
void heap_sort(Element *data, int size, void (*on_step)(Element *, int, int));

#endif /* HEAP_SORT_H */
