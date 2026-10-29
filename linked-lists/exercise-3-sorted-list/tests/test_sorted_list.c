#include "sorted_list.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>

static int float_eq(float a, float b) {
    return fabsf(a - b) < 0.0001f;
}

static void test_empty_list(void) {
    SortedList* list = slist_create();

    assert(slist_is_empty(list));
    assert(slist_size(list) == 0);
    assert(slist_get_min(list) == NULL);
    assert(slist_get_max(list) == NULL);
    assert(slist_get_at(list, 0) == NULL);
    assert(slist_find(list, 1) == NULL);
    assert(!slist_remove(list, 1));
    assert(!slist_update_grade(list, 1, 5.0f));

    slist_destroy(list);
}

static void test_single_element(void) {
    SortedList* list = slist_create();

    assert(slist_insert(list, 10, "Solo", 8.0f));

    assert(!slist_is_empty(list));
    assert(slist_size(list) == 1);
    assert(slist_get_min(list)->ra == 10);
    assert(slist_get_max(list)->ra == 10);
    assert(slist_get_at(list, 0)->ra == 10);

    slist_destroy(list);
}

static void test_insert_keeps_sorted_order(void) {
    SortedList* list = slist_create();

    /* Inserted out of order on purpose. */
    slist_insert(list, 50, "E", 5.0f);
    slist_insert(list, 10, "A", 5.0f);
    slist_insert(list, 30, "C", 5.0f);
    slist_insert(list, 20, "B", 5.0f);
    slist_insert(list, 40, "D", 5.0f);

    assert(slist_size(list) == 5);
    assert(slist_get_at(list, 0)->ra == 10);
    assert(slist_get_at(list, 1)->ra == 20);
    assert(slist_get_at(list, 2)->ra == 30);
    assert(slist_get_at(list, 3)->ra == 40);
    assert(slist_get_at(list, 4)->ra == 50);
    assert(slist_get_min(list)->ra == 10);
    assert(slist_get_max(list)->ra == 50);

    slist_destroy(list);
}

static void test_duplicate_ra_rejected(void) {
    SortedList* list = slist_create();

    assert(slist_insert(list, 10, "Alice", 8.0f));
    assert(!slist_insert(list, 10, "Alice Clone", 9.0f)); /* duplicate RA */
    assert(slist_size(list) == 1);
    assert(slist_find(list, 10)->grade == 8.0f); /* original entry kept */

    slist_destroy(list);
}

static void test_find_and_update_grade(void) {
    SortedList* list = slist_create();

    slist_insert(list, 1, "A", 5.0f);
    slist_insert(list, 2, "B", 6.0f);

    Student* found = slist_find(list, 2);
    assert(found != NULL && found->ra == 2);
    assert(slist_find(list, 999) == NULL);

    assert(slist_update_grade(list, 1, 10.0f));
    assert(float_eq(slist_find(list, 1)->grade, 10.0f));
    assert(!slist_update_grade(list, 999, 0.0f));

    slist_destroy(list);
}

static void test_remove_head_tail_middle(void) {
    SortedList* list = slist_create();

    slist_insert(list, 10, "A", 5.0f);
    slist_insert(list, 20, "B", 5.0f);
    slist_insert(list, 30, "C", 5.0f);

    assert(slist_remove(list, 10)); /* remove head */
    assert(slist_size(list) == 2);
    assert(slist_get_min(list)->ra == 20);

    assert(slist_remove(list, 30)); /* remove tail */
    assert(slist_size(list) == 1);
    assert(slist_get_max(list)->ra == 20);

    assert(!slist_remove(list, 999)); /* not found */

    assert(slist_remove(list, 20)); /* remove the last remaining node */
    assert(slist_is_empty(list));

    slist_destroy(list);
}

static void test_get_at_extremes(void) {
    SortedList* list = slist_create();

    for (unsigned int ra = 0; ra < 6; ra++) {
        slist_insert(list, ra, "X", 5.0f);
    }

    /* Exercises both traversal directions used internally by
       slist_get_at (from the head for the first half, from the tail
       for the second half). */
    assert(slist_get_at(list, 0)->ra == 0);
    assert(slist_get_at(list, 5)->ra == 5);
    assert(slist_get_at(list, 2)->ra == 2);
    assert(slist_get_at(list, 3)->ra == 3);
    assert(slist_get_at(list, 99) == NULL); /* out of bounds */

    slist_destroy(list);
}

int main(void) {
    test_empty_list();
    test_single_element();
    test_insert_keeps_sorted_order();
    test_duplicate_ra_rejected();
    test_find_and_update_grade();
    test_remove_head_tail_middle();
    test_get_at_extremes();

    printf("All sorted_list tests passed.\n");

    return 0;
}
