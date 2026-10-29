#include "student.h"

#include <stdio.h>
#include <stdlib.h>

Student* student_create(unsigned int ra, const char name[NAME_LEN], float grade) {
    Student* s = malloc(sizeof(Student));

    s->ra = ra;
    snprintf(s->name, NAME_LEN, "%s", name);
    s->grade = grade;

    return s;
}

void student_destroy(Student* s) {
    free(s);
}

void student_print(Student* s) {
    printf("%d. %s: %.2f", s->ra, s->name, s->grade);
}

int student_compare(Student* s1, Student* s2) {
    return s1->ra == s2->ra;
}
