#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include <stdbool.h>

#include "student.h"

/**
 * @brief Singly linked list of students, insert-at-head based.
 */
typedef struct StudentList StudentList;

/**
 * @brief Creates an empty student list.
 *
 * @return Pointer to the newly allocated list.
 */
StudentList* list_create(void);

/**
 * @brief Destroys a list, freeing every student and every node.
 *
 * @param list List to destroy.
 */
void list_destroy(StudentList* list);

/**
 * @brief Inserts a new student at the head of the list.
 *
 * @param list Target list.
 * @param ra Registration number.
 * @param name Student name.
 * @param grade Initial grade.
 */
void list_insert_first(StudentList* list, unsigned int ra, const char* name, float grade);

/**
 * @brief Inserts a new student right after a given position.
 *
 * If @p position is less than or equal to zero, or the list is empty,
 * the student is inserted at the head. Otherwise, @p position counts
 * how many hops to take from the head before inserting (so, to insert
 * right after the head node, pass position 1). If @p position walks
 * past the end of the list, the student is inserted at the tail.
 *
 * @param list Target list.
 * @param position Number of hops from the head after which the student is inserted.
 * @param ra Registration number.
 * @param name Student name.
 * @param grade Initial grade.
 */
void list_insert_after(StudentList* list, int position, unsigned int ra, const char* name, float grade);

/**
 * @brief Returns the student at a given position.
 *
 * A negative position returns the head of the list. A position beyond
 * the last valid index returns the tail.
 *
 * @param list Target list.
 * @param position Zero-based position.
 * @return Pointer to the student at that position, or NULL if the list is empty.
 */
Student* list_get(StudentList* list, int position);

/**
 * @brief Prints every student in the list, separated by " -> ".
 *
 * @param list Target list.
 */
void list_print(StudentList* list);

/**
 * @brief Returns the number of students in the list.
 *
 * @param list Target list.
 * @return Current list size.
 */
int list_size(StudentList* list);

/**
 * @brief Checks whether the list has no elements.
 *
 * @param list Target list.
 * @return true if empty, false otherwise.
 */
bool list_is_empty(StudentList* list);

/**
 * @brief Finds a student by registration number.
 *
 * @param list Target list.
 * @param ra Registration number to search for.
 * @return Pointer to the matching student, or NULL if not found.
 */
Student* list_find_by_ra(StudentList* list, unsigned int ra);

/**
 * @brief Adds a fixed amount to every student's grade.
 *
 * @param list Target list.
 * @param amount Amount to add (may be negative).
 */
void list_increment_grades(StudentList* list, float amount);

/**
 * @brief Computes the average grade across all students.
 *
 * @param list Target list.
 * @return Average grade, or 0.0f if the list is empty.
 */
float list_average_grade(StudentList* list);

/**
 * @brief Builds a new list with every student whose grade is below the passing grade.
 *
 * @param list Source list (left untouched).
 * @return Newly allocated list; caller owns it and must call list_destroy().
 */
StudentList* list_filter_failed(StudentList* list);

/**
 * @brief Builds a new list with every student whose grade meets the passing grade.
 *
 * @param list Source list (left untouched).
 * @return Newly allocated list; caller owns it and must call list_destroy().
 */
StudentList* list_filter_passed(StudentList* list);

/**
 * @brief Builds a new list with every student in the final exam grade range.
 *
 * @param list Source list (left untouched).
 * @return Newly allocated list; caller owns it and must call list_destroy().
 */
StudentList* list_filter_exam(StudentList* list);

#endif
