#include <stdio.h>

#include "element.h"

int element_compare(Element a, Element b) {
    return a.key - b.key;
}

void element_print(Element e) {
    printf("%d", e.key);
}

void element_make_array(Element *array, const int *keys, int size) {
    for (int i = 0; i < size; i++) {
        array[i].key = keys[i];
        array[i].name[0] = '\0';
    }
}
