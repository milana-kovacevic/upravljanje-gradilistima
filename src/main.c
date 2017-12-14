#include "database.h"
#include "command.h"
#include "utils.h"


int main(int argc, char **argv)
{
    if (argc == 3)
    {
        connect_to_db("localhost", argv[1], argv[2], "UpravljanjeGradilistima");
    }
    else
    {
        connect_to_db("localhost", "root", "root", "UpravljanjeGradilistima");
    }

    char line[512];
    while (1) {
        printf("> ");
        if (fgets(line, 512, stdin) == NULL || is_empty(line))
        {
            continue;
        }
        execute_command(line);
        printf("\n");
    }

    close_db_connection();

    return 0;
}

