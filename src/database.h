#ifndef _H_DATABASE_H
#define _H_DATABASE_H

#include <mysql.h>
#include "utils.h"

#define LOG

MYSQL *_db;

void connect_to_db( const char *host, const char *user, const char *pass, const char *db);
int execute_query(const char *query);
int get_rows_affected(void);
void close_db_connection();

int print_result(MYSQL_RES *res);

#endif
