#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LEN 50

/**
 * @brief Represents a single student record.
 */
typedef struct {
    unsigned int ra;       /**< Student registration number (unique key). */
    char name[NAME_LEN];   /**< Student name. */
    float grade;           /**< Student grade. */
} Student;

/**
 * @brief Creates a new student on the heap.
 *
 * @param ra Registration number.
 * @param name Student name (copied and truncated to NAME_LEN - 1 chars).
 * @param grade Initial grade.
 * @return Pointer to the newly allocated student.
 */
Student* student_create(unsigned int ra, const char name[NAME_LEN], float grade);

/**
 * @brief Frees the memory associated with a student.
 *
 * @param s Student to destroy.
 */
void student_destroy(Student* s);

/**
 * @brief Compares two students by registration number.
 *
 * @param s1 First student.
 * @param s2 Second student.
 * @return Non-zero if both students share the same RA, zero otherwise.
 */
int student_compare(Student* s1, Student* s2);

/**
 * @brief Prints a student in the format "<ra>. <name>: <grade>".
 *
 * @param s Student to print.
 */
void student_print(Student* s);

#endif
