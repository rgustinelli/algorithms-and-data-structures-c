#include <assert.h>
#include <stdio.h>

#include "heap_sort.h"

/**
 * Checks whether an Element array is sorted in non-increasing
 * (descending) order by key.
 */
static int is_sorted_desc(Element *data, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (element_compare(data[i], data[i + 1]) < 0) {
            return 0;
        }
    }
    return 1;
}

/* Typical unordered input. */
static void test_normal_case(void) {
    const int keys[] = {61, 73, 82, 28, 33, 57, 4, 15};
    int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element data[size];

    element_make_array(data, keys, size);
    heap_sort(data, size, NULL);

    assert(is_sorted_desc(data, size));
    assert(data[0].key == 82);
    assert(data[size - 1].key == 4);
}

/* An empty array must not be touched and must not crash. */
static void test_empty_array(void) {
    Element data[1];
    data[0].key = 0;

    heap_sort(data, 0, NULL);

    assert(data[0].key == 0);
}

/* A single-element array is trivially sorted. */
static void test_single_element(void) {
    const int keys[] = {42};
    Element data[1];

    element_make_array(data, keys, 1);
    heap_sort(data, 1, NULL);

    assert(data[0].key == 42);
}

/* Duplicate keys must be preserved and correctly ordered. */
static void test_duplicate_values(void) {
    const int keys[] = {5, 3, 5, 1, 5, 2};
    int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element data[size];

    element_make_array(data, keys, size);
    heap_sort(data, size, NULL);

    assert(is_sorted_desc(data, size));
    assert(data[0].key == 5);
    assert(data[size - 1].key == 1);
}

/* Input that is already in the target (descending) order. */
static void test_already_sorted_desc(void) {
    const int keys[] = {9, 7, 5, 3, 1};
    int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element data[size];

    element_make_array(data, keys, size);
    heap_sort(data, size, NULL);

    assert(is_sorted_desc(data, size));
    assert(data[0].key == 9);
}

/* Ascending input is the worst case for this descending heap sort. */
static void test_reverse_order_input(void) {
    const int keys[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element data[size];

    element_make_array(data, keys, size);
    heap_sort(data, size, NULL);

    assert(is_sorted_desc(data, size));
    assert(data[0].key == 8);
    assert(data[size - 1].key == 1);
}

/* Negative numbers and extreme values. */
static void test_negative_and_extreme_values(void) {
    const int keys[] = {0, -10, 100, -100, 50, -1};
    int size = (int)(sizeof(keys) / sizeof(keys[0]));
    Element data[size];

    element_make_array(data, keys, size);
    heap_sort(data, size, NULL);

    assert(is_sorted_desc(data, size));
    assert(data[0].key == 100);
    assert(data[size - 1].key == -100);
}

int main(void) {
    test_normal_case();
    test_empty_array();
    test_single_element();
    test_duplicate_values();
    test_already_sorted_desc();
    test_reverse_order_input();
    test_negative_and_extreme_values();

    printf("All tests passed.\n");
    return 0;
}
