/**
 * @file database.h
 * @brief User database indexed simultaneously by email and by id.
 *
 * The database keeps two independent binary search trees over the same set
 * of User records: one ordered by email (BST_Str) and one ordered by id
 * (BST_UInt). Both trees store pointers to the same User instances, so
 * inserting or removing a user keeps both indexes in sync.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"

typedef struct Database Database;

/**
 * Creates an empty database with both indexes initialized.
 * @param None.
 * @return Pointer to a newly created empty database.
 */
Database* db_create(void);

/**
 * Destroys the database's internal indexes. Stored users are not freed;
 * the caller retains ownership of every User passed to db_insert().
 * @param db Database instance to destroy.
 * @return None.
 */
void db_destroy(Database* db);

/**
 * Looks up a user by email.
 * @param db Database instance to query.
 * @param email Email key to search for.
 * @return Pointer to the matching user, or NULL if not found.
 */
User* db_query_by_email(Database* db, const char* email);

/**
 * Looks up a user by id.
 * @param db Database instance to query.
 * @param id Id key to search for.
 * @return Pointer to the matching user, or NULL if not found.
 */
User* db_query_by_id(Database* db, unsigned int id);

/**
 * Inserts a user into both the email and id indexes.
 * @param db Database instance to modify.
 * @param user User to insert. Ownership stays with the caller.
 * @return None.
 */
void db_insert(Database* db, User* user);

/**
 * Removes the user with the given email from both indexes, if present.
 * @param db Database instance to modify.
 * @param email Email key to remove.
 * @return None.
 */
void db_remove_by_email(Database* db, const char* email);

/**
 * Removes the user with the given id from both indexes, if present.
 * @param db Database instance to modify.
 * @param id Id key to remove.
 * @return None.
 */
void db_remove_by_id(Database* db, unsigned int id);

void db_print_pre_order_by_email(Database* db);
void db_print_in_order_by_email(Database* db);
void db_print_post_order_by_email(Database* db);

void db_print_pre_order_by_id(Database* db);
void db_print_in_order_by_id(Database* db);
void db_print_post_order_by_id(Database* db);

/**
 * Returns the number of users currently stored (counted via the id index).
 * @param db Database instance to inspect.
 * @return Number of users currently stored.
 */
int db_size(Database* db);

#endif
