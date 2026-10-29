#include "linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <limits.h>

static void test_empty_list(void) {
    LinkedList* list = list_create();

    assert(list_is_empty(list));
    assert(list_size(list) == 0);
    assert(list_get_first(list) == INT_MIN); /* element_null() sentinel */
    assert(list_get_last(list) == INT_MIN);
    assert(list_get_at(list, 0) == INT_MIN);

    list_destroy(list);
}

static void test_single_element(void) {
    LinkedList* list = list_create();

    list_insert_last(list, 42);

    assert(!list_is_empty(list));
    assert(list_size(list) == 1);
    assert(list_get_first(list) == 42);
    assert(list_get_last(list) == 42);
    assert(list_get_at(list, 0) == 42);

    list_remove_last(list);

    assert(list_is_empty(list));
    assert(list_size(list) == 0);

    list_destroy(list);
}

static void test_insert_last_and_get(void) {
    LinkedList* list = list_create();

    for (int i = 1; i <= 5; i++) {
        list_insert_last(list, i * 10);
    }

    assert(list_size(list) == 5);
    assert(list_get_first(list) == 10);
    assert(list_get_last(list) == 50);
    assert(list_get_at(list, 2) == 30);
    assert(list_get_at(list, 99) == INT_MIN); /* out of bounds */

    list_destroy(list);
}

static void test_insert_first_and_at(void) {
    LinkedList* list = list_create();

    list_insert_last(list, 20);
    list_insert_last(list, 30);
    list_insert_first(list, 10); /* 10 -> 20 -> 30 */
    list_insert_at(list, 2, 25); /* 10 -> 20 -> 25 -> 30 */

    assert(list_size(list) == 4);
    assert(list_get_at(list, 0) == 10);
    assert(list_get_at(list, 1) == 20);
    assert(list_get_at(list, 2) == 25);
    assert(list_get_at(list, 3) == 30);
    assert(list_get_last(list) == 30);

    list_destroy(list);
}

static void test_insert_at_bounds_and_tail_update(void) {
    LinkedList* list = list_create();

    list_insert_last(list, 1);

    /* list_insert_at only accepts an existing index (it shifts the
       element currently there); position == size is out of range and
       must be rejected, unlike list_insert_last(). */
    list_insert_at(list, 1, 99);
    assert(list_size(list) == 1);

    /* Inserting at a valid last index shifts the old tail and must
       update list->last correctly. */
    list_insert_at(list, 0, 2); /* 2 -> 1 */
    assert(list_size(list) == 2);
    assert(list_get_first(list) == 2);
    assert(list_get_last(list) == 1);

    list_destroy(list);
}

static void test_remove_first_last_at(void) {
    LinkedList* list = list_create();

    for (int i = 1; i <= 4; i++) {
        list_insert_last(list, i);
    }
    /* list: 1 -> 2 -> 3 -> 4 */

    list_remove_first(list); /* 2 -> 3 -> 4 */
    assert(list_get_first(list) == 2);
    assert(list_size(list) == 3);

    list_remove_last(list); /* 2 -> 3 */
    assert(list_get_last(list) == 3);
    assert(list_size(list) == 2);

    list_remove_at(list, 0); /* 3 */
    assert(list_size(list) == 1);
    assert(list_get_first(list) == 3);
    assert(list_get_last(list) == 3);

    list_destroy(list);
}

static void test_remove_from_empty_is_safe(void) {
    LinkedList* list = list_create();

    /* These are no-ops on an empty list; they must not crash and must
       print an error through list_error() (visible on stderr). */
    list_remove_first(list);
    list_remove_last(list);
    list_remove_at(list, 0);

    assert(list_is_empty(list));

    list_destroy(list);
}

static void test_duplicate_values(void) {
    LinkedList* list = list_create();

    list_insert_last(list, 7);
    list_insert_last(list, 7);
    list_insert_last(list, 7);

    assert(list_size(list) == 3);
    assert(element_compare(&(Element){7}, &(Element){7}) == 0);

    list_remove_at(list, 1);
    assert(list_size(list) == 2);
    assert(list_get_at(list, 0) == 7);
    assert(list_get_at(list, 1) == 7);

    list_destroy(list);
}

int main(void) {
    test_empty_list();
    test_single_element();
    test_insert_last_and_get();
    test_insert_first_and_at();
    test_insert_at_bounds_and_tail_update();
    test_remove_first_last_at();
    test_remove_from_empty_is_safe();
    test_duplicate_values();

    printf("All linked_list tests passed.\n");

    return 0;
}
