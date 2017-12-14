#include <stdio.h>
#include <mysql.h>
#include "database.h"

MYSQL *_db = NULL;

void connect_to_db(const char *host, const char *user, const char *pass, const char *db)
{
#ifdef LOG
    printf("Connecting to database '%s'... ", db);
    fflush(stdout);
#endif
    _db = mysql_init(NULL);
    if (!mysql_real_connect(_db, host, user, pass, db, 0, NULL, 0))
    {
        error_fatal("\nConnecting to database failed. Error:\n", mysql_error(_db));
    }
#ifdef LOG
    printf("Connected.\n");
#endif
}

int execute_query(const char *query)
{
#ifdef LOG
    printf("Executing query: %s\n", query);
#endif
    if (_db == NULL)
    {
        return 0;
    }
    
    if (mysql_query(_db, query))
    {
        error_info("Error:\n%s\n", mysql_error(_db));
        return 0;
    }

    MYSQL_RES *res = mysql_use_result(_db);
    if (res != NULL)
    {
        printf("Printing results...\n");
        print_result(res);
        printf("Done.\n");
        mysql_free_result(res);
    }
#ifdef LOG
    printf("Query successfully executed.");
#endif
    return 1;
}

void print_result(MYSQL_RES *res)
{
    int col_num = mysql_num_fields(res);

    MYSQL_FIELD *field = mysql_fetch_field(res);
    printf("| ");
    for (int i = 0; i < col_num; i++)
        printf("%20s | ", field[i].name);
    putchar('\n');

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != 0)
    {
        printf("| ");
        for (int i = 0; i < col_num; i++)
            printf("%20.*s | ", 20, row[i]);
        putchar('\n');
    }
}

void close_db_connection()
{
    if (_db != NULL)
    {
#ifdef LOG
        printf("Closing database connection... ");
#endif
        mysql_close(_db);
        _db = NULL;
#ifdef LOG
        printf("Done.\n");
#endif
    }
}

