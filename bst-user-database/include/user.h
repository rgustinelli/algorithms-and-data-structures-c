/**
 * @file user.h
 * @brief User record definition and lifecycle management.
 */
#ifndef USER_H
#define USER_H

typedef struct User {
    unsigned int id;
    char email[256];
    char name[256];
    char password[256];
} User;

/**
 * Prints a user's fields to stdout as "id, email, name, password".
 * @param user User to print.
 * @return None.
 */
void user_print(User* user);

/**
 * Allocates and initializes a new user record.
 *
 * The email, name and password strings are copied into fixed-size internal
 * buffers (255 characters plus a null terminator); longer inputs are
 * truncated.
 *
 * @param id Unique identifier for the user.
 * @param email User's email address.
 * @param name User's display name.
 * @param password User's password.
 * @return Pointer to the newly allocated user. The caller owns this memory
 *         and must release it with user_destroy().
 */
User* user_create(unsigned int id, const char* email, const char* name, const char* password);

/**
 * Releases the memory owned by a user record.
 * @param user User to destroy.
 * @return None.
 */
void user_destroy(User* user);

#endif
