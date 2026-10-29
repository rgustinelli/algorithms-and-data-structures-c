#include "sorted_list.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    Student* student;
    struct Node* next;
    struct Node* prev;
} Node;

struct SortedList {
    Node* sentinel;
    size_t size;
};

/**
 * @brief Allocates a node and its student payload.
 *
 * @param ra Registration number.
 * @param name Student name.
 * @param grade Initial grade.
 * @return Newly allocated node (not yet linked into any list).
 */
static Node* create_node(unsigned int ra, const char* name, float grade) {
    Node* new_node = malloc(sizeof(Node));

    new_node->student = student_create(ra, name, grade);
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

/**
 * @brief Checks whether a position is within the bounds of the list.
 *
 * @param list Target list.
 * @param pos Zero-based position to validate.
 * @return true if pos < list->size, false otherwise.
 */
static bool is_position_valid(SortedList* list, size_t pos) {
    return pos < list->size;
}

/**
 * @brief Prints a standardized error message to stderr.
 *
 * @param message Description of the error.
 */
static void log_error(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
}

SortedList* slist_create(void) {
    SortedList* list = malloc(sizeof(SortedList));

    list->sentinel = malloc(sizeof(Node));
    list->sentinel->student = NULL;
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;

    list->size = 0;

    return list;
}

void slist_destroy(SortedList* list) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel) {
        Node* trash = cur;

        cur = cur->next;
        student_destroy(trash->student);
        free(trash);
    }
    free(list->sentinel);
    free(list);
}

size_t slist_size(SortedList* list) {
    return list->size;
}

Student* slist_get_at(SortedList* list, size_t pos) {
    if (!is_position_valid(list, pos)) {
        log_error("Invalid position");

        return NULL;
    }

    Node* cur;

    if (pos < list->size / 2) {
        cur = list->sentinel->next;
        for (size_t i = 0; i < pos; i++) {
            cur = cur->next;
        }
    } else {
        cur = list->sentinel->prev;
        for (size_t i = list->size - 1; i > pos; i--) {
            cur = cur->prev;
        }
    }

    return cur->student;
}

Student* slist_get_min(SortedList* list) {
    if (slist_is_empty(list)) {
        log_error("List is empty");

        return NULL;
    }

    return list->sentinel->next->student;
}

Student* slist_get_max(SortedList* list) {
    if (slist_is_empty(list)) {
        log_error("List is empty");

        return NULL;
    }

    return list->sentinel->prev->student;
}

bool slist_is_empty(SortedList* list) {
    return list->sentinel->next == list->sentinel;
}

void slist_print(SortedList* list) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel) {
        student_print(cur->student);
        if (cur->next != list->sentinel) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

bool slist_insert(SortedList* list, unsigned int ra, const char* name, float grade) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel && cur->student->ra < ra) {
        cur = cur->next;
    }

    if (cur != list->sentinel && cur->student->ra == ra) {
        return false;
    }

    Node* new_node = create_node(ra, name, grade);

    new_node->next = cur;
    new_node->prev = cur->prev;

    cur->prev->next = new_node;
    cur->prev = new_node;

    list->size++;

    return true;
}

bool slist_remove(SortedList* list, unsigned int ra) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel && cur->student->ra != ra) {
        cur = cur->next;
    }

    if (cur == list->sentinel) {
        return false;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    student_destroy(cur->student);
    free(cur);

    list->size--;

    return true;
}

Student* slist_find(SortedList* list, unsigned int ra) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel) {
        if (cur->student->ra == ra) {
            return cur->student;
        }
        cur = cur->next;
    }

    return NULL;
}

bool slist_update_grade(SortedList* list, unsigned int ra, float new_grade) {
    Node* cur = list->sentinel->next;

    while (cur != list->sentinel) {
        if (cur->student->ra == ra) {
            cur->student->grade = new_grade;
            return true;
        }
        cur = cur->next;
    }

    return false;
}
