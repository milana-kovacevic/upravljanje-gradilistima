#include "database.h"
#include "command.h"
#include "utils.h"
#include "menu.h"


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

    printf("Welcome!\n");

    while (1) {
        print_main_menu();
        enter_and_execute_command();
    }

    close_db_connection();

    return 0;
}

