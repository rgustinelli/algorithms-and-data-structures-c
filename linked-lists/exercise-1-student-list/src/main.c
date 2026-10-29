#include "student_list.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    StudentList* list = list_create();

    list_insert_first(list, 123, "John", 7.0);
    list_insert_first(list, 456, "Mary", 3.0);
    list_insert_first(list, 789, "Peter", 6.0);
    list_insert_first(list, 101, "Alice", 1.0);

    list_print(list);

    Student* s = list_find_by_ra(list, 456);
    if (s != NULL) {
        printf("Student found: %s\n", s->name);
    } else {
        printf("Student not found\n");
    }

    Student* s2 = list_find_by_ra(list, 999);
    if (s2 != NULL) {
        printf("Student found: %s\n", s2->name);
    } else {
        printf("Student not found\n");
    }

    list_increment_grades(list, 1.0);
    list_print(list);

    float avg = list_average_grade(list);
    printf("Average grade: %.2f\n", avg);

    StudentList* failed = list_filter_failed(list);
    printf("Failed students:\n");
    list_print(failed);

    StudentList* passed = list_filter_passed(list);
    printf("Passed students:\n");
    list_print(passed);

    StudentList* exam = list_filter_exam(list);
    printf("Students that need to take the exam:\n");
    list_print(exam);

    list_destroy(list);
    list_destroy(failed);
    list_destroy(passed);
    list_destroy(exam);

    return 0;
}
