#include "student_list.h"

#include <stdlib.h>
#include <stdio.h>

#define PASSING_GRADE 6.0f
#define EXAM_LOWER_BOUND 4.0f
#define EXAM_UPPER_BOUND 6.0f

typedef struct Node {
    Student* student;
    struct Node* next;
} Node;

struct StudentList {
    Node* head;
};

StudentList* list_create(void) {
    StudentList* list = malloc(sizeof(StudentList));

    list->head = NULL;

    return list;
}

void list_destroy(StudentList* list) {
    Node* trash = list->head;

    while (trash != NULL) {
        list->head = trash->next;

        student_destroy(trash->student);
        free(trash);
        trash = list->head;
    }
    free(list);
}

void list_insert_first(StudentList* list, unsigned int ra, const char* name, float grade) {
    Node* new_node = malloc(sizeof(Node));

    new_node->student = student_create(ra, name, grade);
    new_node->next = list->head;
    list->head = new_node;
}

void list_insert_after(StudentList* list, int position, unsigned int ra, const char* name, float grade) {
    if (position <= 0 || list->head == NULL) {
        list_insert_first(list, ra, name, grade);
    } else {
        Node* cur = list->head;
        int i = 0;

        while (i < position && cur->next != NULL) {
            cur = cur->next;
            i++;
        }

        Node* new_node = malloc(sizeof(Node));

        new_node->student = student_create(ra, name, grade);
        new_node->next = cur->next;
        cur->next = new_node;
    }
}

Student* list_get(StudentList* list, int position) {
    if (list->head == NULL) {
        return NULL;
    }

    if (position < 0) {
        return list->head->student;
    }

    Node* cur = list->head;
    int i = 0;

    while (i < position && cur->next != NULL) {
        cur = cur->next;
        i++;
    }

    return cur->student;
}

void list_print(StudentList* list) {
    Node* cur = list->head;

    while (cur != NULL) {
        student_print(cur->student);
        if (cur->next != NULL) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

int list_size(StudentList* list) {
    Node* cur = list->head;
    int count = 0;

    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}

bool list_is_empty(StudentList* list) {
    return list->head == NULL;
}

Student* list_find_by_ra(StudentList* list, unsigned int ra) {
    Node* cur = list->head;

    while (cur != NULL) {
        if (cur->student->ra == ra) {
            return cur->student;
        }
        cur = cur->next;
    }

    return NULL;
}

void list_increment_grades(StudentList* list, float amount) {
    Node* cur = list->head;

    while (cur != NULL) {
        cur->student->grade += amount;
        cur = cur->next;
    }
}

float list_average_grade(StudentList* list) {
    Node* cur = list->head;
    float sum = 0.0f;
    int count = 0;

    while (cur != NULL) {
        sum += cur->student->grade;
        count++;
        cur = cur->next;
    }

    if (count == 0) {
        return 0.0f;
    }

    return sum / (float)count;
}

StudentList* list_filter_failed(StudentList* list) {
    StudentList* new_list = list_create();
    Node* cur = list->head;

    while (cur != NULL) {
        if (cur->student->grade < PASSING_GRADE) {
            list_insert_first(
                new_list,
                cur->student->ra,
                cur->student->name,
                cur->student->grade
            );
        }
        cur = cur->next;
    }

    return new_list;
}

StudentList* list_filter_passed(StudentList* list) {
    StudentList* new_list = list_create();
    Node* cur = list->head;

    while (cur != NULL) {
        if (cur->student->grade >= PASSING_GRADE) {
            list_insert_first(
                new_list,
                cur->student->ra,
                cur->student->name,
                cur->student->grade
            );
        }
        cur = cur->next;
    }

    return new_list;
}

StudentList* list_filter_exam(StudentList* list) {
    StudentList* new_list = list_create();
    Node* cur = list->head;

    while (cur != NULL) {
        float grade = cur->student->grade;

        if (grade >= EXAM_LOWER_BOUND && grade < EXAM_UPPER_BOUND) {
            list_insert_first(
                new_list,
                cur->student->ra,
                cur->student->name,
                cur->student->grade
            );
        }

        cur = cur->next;
    }

    return new_list;
}
