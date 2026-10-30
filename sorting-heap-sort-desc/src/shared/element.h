#ifndef ELEMENT_H
#define ELEMENT_H

#define ELEMENT_NAME_MAX 50

/**
 * Represents a single element handled by the sorting algorithms in
 * this project: a sortable integer key plus a name label.
 *
 * The name field exists to support inputs that carry a label beyond
 * their sort key. When an Element array is built from a plain array
 * of integer keys (see element_make_array), there is no name data
 * available, so name is left as an empty string.
 */
typedef struct {
    int key;
    char name[ELEMENT_NAME_MAX];
} Element;

/**
 * Compares two elements by their key.
 *
 * @param a First element.
 * @param b Second element.
 * @return A negative value if a.key < b.key, zero if the keys are
 *         equal, and a positive value if a.key > b.key.
 */
int element_compare(Element a, Element b);

/**
 * Prints an element to stdout.
 *
 * Only the key is printed. name is intentionally left out here: for
 * this project, elements are built from plain integer keys with no
 * associated name (see element_make_array), so there is nothing
 * meaningful to print for that field.
 *
 * @param e Element to print.
 */
void element_print(Element e);

/**
 * Builds an array of Element from an array of integer keys.
 *
 * Each element's key is set from the corresponding entry in keys.
 * The name field is left as an empty string, since a plain integer
 * key array carries no name data to populate it with.
 *
 * @param array Destination array of Element, with at least size slots.
 * @param keys  Source array of integer keys.
 * @param size  Number of elements to build.
 */
void element_make_array(Element *array, const int *keys, int size);

#endif /* ELEMENT_H */
