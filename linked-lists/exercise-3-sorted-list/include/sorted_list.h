#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "student.h"

/**
 * @brief Doubly linked, circular list of students kept sorted by
 * ascending registration number (RA).
 */
typedef struct SortedList SortedList;

/**
 * @brief Creates an empty sorted list.
 *
 * The list is implemented as a doubly linked circular list with a sentinel node.
 *
 * @return Pointer to the created list, or NULL if allocation fails.
 */
SortedList* slist_create(void);

/**
 * @brief Destroys a list and frees all associated memory.
 *
 * Frees every node, every stored student, the sentinel node, and the list itself.
 *
 * @param list List to destroy.
 */
void slist_destroy(SortedList* list);

/**
 * @brief Returns the number of students currently stored.
 *
 * @param list Target list.
 * @return Current list size.
 */
size_t slist_size(SortedList* list);

/**
 * @brief Returns the student at a given position.
 *
 * Takes advantage of the doubly linked structure to traverse from the closer end for efficiency.
 *
 * @param list Target list.
 * @param pos Zero-based position.
 * @return Pointer to the student at position @p pos, or NULL if out of bounds.
 */
Student* slist_get_at(SortedList* list, size_t pos);

/**
 * @brief Returns the student with the smallest RA.
 *
 * @param list Target list.
 * @return Pointer to the smallest-RA student, or NULL if the list is empty.
 */
Student* slist_get_min(SortedList* list);

/**
 * @brief Returns the student with the largest RA.
 *
 * @param list Target list.
 * @return Pointer to the largest-RA student, or NULL if the list is empty.
 */
Student* slist_get_max(SortedList* list);

/**
 * @brief Checks whether the list has no elements.
 *
 * @param list Target list.
 * @return true if the list is empty, otherwise false.
 */
bool slist_is_empty(SortedList* list);

/**
 * @brief Prints list contents in sorted order.
 *
 * @param list Target list.
 */
void slist_print(SortedList* list);

/* New functions added on top of the base list interface. */

/**
 * @brief Inserts a new student, keeping the list sorted by RA.
 *
 * @param list Target list.
 * @param ra Registration number (used as the sort key and uniqueness check).
 * @param name Student name.
 * @param grade Initial grade.
 * @return true if the student was inserted, false if a student with the
 *         same RA already exists (no duplicates are allowed).
 */
bool slist_insert(SortedList* list, unsigned int ra, const char* name, float grade);

/**
 * @brief Removes the student with a given RA, if present.
 *
 * @param list Target list.
 * @param ra Registration number to remove.
 * @return true if a student was found and removed, false otherwise.
 */
bool slist_remove(SortedList* list, unsigned int ra);

/**
 * @brief Finds the student with a given RA.
 *
 * @param list Target list.
 * @param ra Registration number to search for.
 * @return Pointer to the matching student, or NULL if not found.
 */
Student* slist_find(SortedList* list, unsigned int ra);

/**
 * @brief Updates the grade of the student with a given RA.
 *
 * @param list Target list.
 * @param ra Registration number to search for.
 * @param new_grade New grade value.
 * @return true if the student was found and updated, false otherwise.
 */
bool slist_update_grade(SortedList* list, unsigned int ra, float new_grade);

#endif
