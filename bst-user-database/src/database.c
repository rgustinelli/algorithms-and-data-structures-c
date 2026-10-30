/**
 * @file database.c
 * @brief User database implementation combining an email index and an id index.
 */
#include "database.h"
#include "bst_str.h"
#include "bst_uint.h"

#include <stdlib.h>

struct Database {
    BST_Str* email_index;
    BST_UInt* id_index;
};

Database* db_create(void) {
    Database* db = malloc(sizeof(Database));

    db->email_index = bst_str_create();
    db->id_index = bst_uint_create();

    return db;
}

void db_destroy(Database* db) {
    bst_str_destroy(db->email_index);
    bst_uint_destroy(db->id_index);
    free(db);
}

User* db_query_by_email(Database* db, const char* email) {
    return bst_str_query(db->email_index, email);
}

User* db_query_by_id(Database* db, unsigned int id) {
    return bst_uint_query(db->id_index, id);
}

void db_insert(Database* db, User* user) {
    bst_str_insert(db->email_index, user);
    bst_uint_insert(db->id_index, user);
}

void db_remove_by_email(Database* db, const char* email) {
    User* user = bst_str_query(db->email_index, email);

    if (user != NULL) {
        bst_str_remove(db->email_index, email);
        bst_uint_remove(db->id_index, user->id);
    }
}

void db_remove_by_id(Database* db, unsigned int id) {
    User* user = bst_uint_query(db->id_index, id);

    if (user != NULL) {
        bst_uint_remove(db->id_index, id);
        bst_str_remove(db->email_index, user->email);
    }
}

void db_print_pre_order_by_email(Database* db) {
    bst_str_print_pre_order(db->email_index);
}

void db_print_in_order_by_email(Database* db) {
    bst_str_print_in_order(db->email_index);
}

void db_print_post_order_by_email(Database* db) {
    bst_str_print_post_order(db->email_index);
}

void db_print_pre_order_by_id(Database* db) {
    bst_uint_print_pre_order(db->id_index);
}

void db_print_in_order_by_id(Database* db) {
    bst_uint_print_in_order(db->id_index);
}

void db_print_post_order_by_id(Database* db) {
    bst_uint_print_post_order(db->id_index);
}

int db_size(Database* db) {
    return bst_uint_size(db->id_index);
}
