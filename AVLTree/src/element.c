//Implementation of element helper functions.

#include "element.h"

#include <stdio.h>

void element_print(Element element) {
    printf("%d", element);
}

int element_compare(Element a, Element b) {
    return (a > b) - (a < b);
}
