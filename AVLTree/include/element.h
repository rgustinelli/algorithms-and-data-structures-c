/**
 * @file element.h
 * @brief Definition of the element type and helper functions.
 */

#ifndef ELEMENT_H
#define ELEMENT_H

/**
 * @brief Type stored by the AVL tree.
 *
 * This alias allows the stored type to be changed without requiring
 * modifications to the AVL tree implementation.
 */
typedef int Element;

/**
 * @brief Prints an element.
 *
 * @param element Element to be printed.
 */
void element_print(Element element);

/**
 * @brief Compares two elements.
 *
 * @param a First element.
 * @param b Second element.
 *
 * @return
 *   - Negative if a < b
 *   - Zero if a == b
 *   - Positive if a > b
 */
int element_compare(Element a, Element b);

#endif /* ELEMENT_H */
