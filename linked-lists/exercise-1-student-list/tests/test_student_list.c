#include "student_list.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>

static int float_eq(float a, float b) {
    return fabsf(a - b) < 0.0001f;
}

static void test_empty_list(void) {
    StudentList* list = list_create();

    assert(list_is_empty(list));
    assert(list_size(list) == 0);
    assert(float_eq(list_average_grade(list), 0.0f));

    list_destroy(list);
}

static void test_insert_first_order(void) {
    StudentList* list = list_create();

    list_insert_first(list, 1, "A", 5.0f);
    list_insert_first(list, 2, "B", 6.0f);
    list_insert_first(list, 3, "C", 7.0f);

    /* insert_first always pushes to the head, so the last inserted
       student must come first. */
    assert(list_get(list, 0)->ra == 3);
    assert(list_get(list, 1)->ra == 2);
    assert(list_get(list, 2)->ra == 1);
    assert(list_size(list) == 3);
    assert(!list_is_empty(list));

    list_destroy(list);
}

static void test_insert_after(void) {
    StudentList* list = list_create();

    /* NOTE: position <= 0 is treated as "insert at head" (see
       list_insert_after's documentation); to insert right after the
       head node, position 1 must be used. */
    list_insert_first(list, 1, "A", 5.0f);
    list_insert_after(list, 1, 2, "B", 6.0f);  /* becomes: 1 -> 2 */
    list_insert_after(list, 10, 3, "C", 7.0f); /* out of range -> appended at tail */

    assert(list_size(list) == 3);
    assert(list_get(list, 0)->ra == 1);
    assert(list_get(list, 1)->ra == 2);
    assert(list_get(list, 2)->ra == 3);

    list_destroy(list);
}

static void test_find_by_ra(void) {
    StudentList* list = list_create();

    list_insert_first(list, 10, "Alice", 8.0f);
    list_insert_first(list, 20, "Bob", 5.0f);

    Student* found = list_find_by_ra(list, 10);
    Student* missing = list_find_by_ra(list, 999);

    assert(found != NULL && found->ra == 10);
    assert(missing == NULL);

    list_destroy(list);
}

static void test_increment_and_average(void) {
    StudentList* list = list_create();

    list_insert_first(list, 1, "A", 4.0f);
    list_insert_first(list, 2, "B", 6.0f);

    assert(float_eq(list_average_grade(list), 5.0f));

    list_increment_grades(list, 1.0f);

    assert(float_eq(list_get(list, 0)->grade, 7.0f));
    assert(float_eq(list_get(list, 1)->grade, 5.0f));

    list_destroy(list);
}

static void test_filters(void) {
    /* Grading scheme used by the original implementation:
       - "failed"  -> grade  < PASSING_GRADE (6.0)
       - "passed"  -> grade >= PASSING_GRADE (6.0)
       - "exam"    -> grade in [EXAM_LOWER_BOUND, EXAM_UPPER_BOUND) = [4.0, 6.0)
       Note that "failed" and "exam" intentionally overlap: a student
       with a grade between 4.0 and 6.0 is reported as failed AND as
       eligible for the exam, matching the reference program's output. */
    StudentList* list = list_create();

    list_insert_first(list, 1, "Failed", 2.0f);    /* < 4.0            */
    list_insert_first(list, 2, "Exam", 5.0f);      /* [4.0, 6.0)       */
    list_insert_first(list, 3, "Passed", 9.0f);    /* >= 6.0           */
    list_insert_first(list, 4, "Boundary", 6.0f);  /* == 6.0 -> passed */

    StudentList* failed = list_filter_failed(list);
    StudentList* passed = list_filter_passed(list);
    StudentList* exam = list_filter_exam(list);

    assert(list_size(failed) == 2); /* ra 1 and ra 2 */
    assert(list_size(passed) == 2); /* ra 3 and ra 4 */

    assert(list_size(exam) == 1);
    assert(list_get(exam, 0)->ra == 2);

    list_destroy(list);
    list_destroy(failed);
    list_destroy(passed);
    list_destroy(exam);
}

static void test_single_element(void) {
    StudentList* list = list_create();

    list_insert_first(list, 42, "Solo", 10.0f);

    assert(list_size(list) == 1);
    assert(!list_is_empty(list));
    assert(list_get(list, 0)->ra == 42);
    assert(list_get(list, 5)->ra == 42); /* out-of-range clamps to tail */
    assert(list_get(list, -1)->ra == 42); /* negative clamps to head */

    list_destroy(list);
}

int main(void) {
    test_empty_list();
    test_insert_first_order();
    test_insert_after();
    test_find_by_ra();
    test_increment_and_average();
    test_filters();
    test_single_element();

    printf("All student_list tests passed.\n");

    return 0;
}
