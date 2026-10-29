#ifndef ELEMENT_H
#define ELEMENT_H

/**
 * @brief Type of value stored by the generic linked list.
 *
 * The list is "generic" only in the sense that all element-specific
 * logic (comparison, printing, the sentinel "null" value) is isolated
 * in this module. Swapping Element to another type only requires
 * updating element.h/element.c.
 */
typedef int Element;

/**
 * @brief Compares two elements.
 *
 * @param element1 First element.
 * @param element2 Second element.
 * @return Negative if element1 < element2, zero if equal, positive if greater.
 */
int element_compare(Element* element1, Element* element2);

/**
 * @brief Prints an element with no trailing newline.
 *
 * @param element Element to print.
 */
void element_print(Element* element);

/**
 * @brief Sentinel value returned by list operations that fail
 * (e.g. reading from an invalid position or an empty list).
 *
 * @return The sentinel "null" element.
 */
Element element_null(void);

#endif
