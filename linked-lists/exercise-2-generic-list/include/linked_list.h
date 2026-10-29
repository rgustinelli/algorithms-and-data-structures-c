#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "element.h"

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Singly linked list of Element values, tracking both ends
 * (first/last) and its size for O(1) size queries and tail insertion.
 */
typedef struct LinkedList LinkedList;

/**
 * @brief Creates an empty list.
 *
 * @return Pointer to the newly allocated list.
 */
LinkedList* list_create(void);

/**
 * @brief Destroys a list, freeing every node.
 *
 * @param list List to destroy.
 */
void list_destroy(LinkedList* list);

/**
 * @brief Inserts an element at the end of the list.
 *
 * @param list Target list.
 * @param element Element to insert.
 */
void list_insert_last(LinkedList* list, Element element);

/**
 * @brief Returns the element at a given position.
 *
 * @param list Target list.
 * @param position Zero-based position.
 * @return The element at that position, or element_null() if the position is invalid.
 */
Element list_get_at(LinkedList* list, size_t position);

/**
 * @brief Returns the first element of the list.
 *
 * @param list Target list.
 * @return The first element, or element_null() if the list is empty.
 */
Element list_get_first(LinkedList* list);

/**
 * @brief Returns the last element of the list.
 *
 * @param list Target list.
 * @return The last element, or element_null() if the list is empty.
 */
Element list_get_last(LinkedList* list);

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list Target list.
 * @return Current list size.
 */
size_t list_size(LinkedList* list);

/**
 * @brief Checks whether the list has no elements.
 *
 * @param list Target list.
 * @return true if empty, false otherwise.
 */
bool list_is_empty(LinkedList* list);

/**
 * @brief Prints every element in the list, separated by " -> ".
 *
 * @param list Target list.
 */
void list_print(LinkedList* list);

/* New functions added on top of the base list interface. */

/**
 * @brief Inserts an element at the beginning of the list.
 *
 * @param list Target list.
 * @param element Element to insert.
 */
void list_insert_first(LinkedList* list, Element element);

/**
 * @brief Inserts an element at a given position, shifting the rest of
 * the list one position to the right.
 *
 * @param list Target list.
 * @param position Zero-based position where the element will end up.
 * @param element Element to insert.
 */
void list_insert_at(LinkedList* list, size_t position, Element element);

/**
 * @brief Removes the first element of the list.
 *
 * @param list Target list.
 */
void list_remove_first(LinkedList* list);

/**
 * @brief Removes the last element of the list.
 *
 * @param list Target list.
 */
void list_remove_last(LinkedList* list);

/**
 * @brief Removes the element at a given position.
 *
 * @param list Target list.
 * @param position Zero-based position to remove.
 */
void list_remove_at(LinkedList* list, size_t position);

#endif
