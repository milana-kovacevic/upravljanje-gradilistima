#include "command.h"

void execute_command(char *command_line)
{
    int args_num;
    char **args = parse_command_line(command_line, &args_num);
    if (!strcmp(args[0], "izlistaj-gradilista") || !strcmp(args[0], "ig"))
    {
        izlistaj_gradilista(args, args_num);
    }
    else if (!strcmp(args[0], "dodaj-gradiliste") || !strcmp(args[0], "dg"))
    {
        dodaj_gradiliste(args, args_num);
    }
    else if (!strcmp(args[0], "obrisi-gradiliste") || !strcmp(args[0], "og"))
    {
        obrisi_gradiliste(args, args_num);
    }
    else if (!strcmp(args[0], "izlistaj-firme") || !strcmp(args[0], "if"))
    {
        izlistaj_firme();
    }
    else if (!strcmp(args[0], "dodaj-firmu") || !strcmp(args[0], "df"))
    {
        dodaj_firmu(args, args_num);
    }
    else if (!strcmp(args[0], "obrisi-firmu") || !strcmp(args[0], "of"))
    {
        obrisi_firmu(args, args_num);
    }
    else if (!strcmp(args[0], "help") || !strcmp(args[0], "h"))
    {
        usage();
    }
    else if (!strncmp(args[0], "query", strlen("query")))
    {
        if (!execute_query(command_line + strlen("query") + 1))
        {
            error_info("Error when executing query: %s", command_line + strlen("query") + 1);
        }
    }
    else if (!strcmp(args[0], "exit") || !strcmp(args[0], "bye") || !strcmp(args[0], "poy"))
    {
        close_db_connection();
        printf("Bye!\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Unknown command.");
    }
    
    free_args(args, args_num);
}

void izlistaj_gradilista(char **args, int args_num)
{
    char query[MAX_QUERY];
    int offset = sprintf(query, "SELECT * FROM Gradiliste ");
    if (args_num == 2)
    {
        sprintf(query + offset, "WHERE Status = \"%s\"", args[1]);
    }
    execute_query(query);
}

void dodaj_gradiliste(char **args, int args_num)
{
    if (!assert(args_num == 4, "Dodavanje gradilista zahteva naziv, adresu i status."))
    {
        return;
    }
    char query[MAX_QUERY];
    sprintf (query, "INSERT INTO Gradiliste (Naziv, Adresa, Status) "
            "VALUES (\"%s\", \"%s\", \"%s\")", args[1], args[2], args[3]);
    execute_query(query);
}

void obrisi_gradiliste(char **args, int args_num)
{
    if (!assert(args_num == 2, "Brisanje gradilista zahteva id."))
    {
        return;
    }
    char query[MAX_QUERY];
    sprintf (query, "DELETE FROM Gradiliste WHERE idGradilista = %s", args[1]);
    execute_query(query);
}

void izlistaj_firme(void)
{
    execute_query("SELECT * FROM Firma");
}

void dodaj_firmu(char **args, int args_num)
{
    if (!assert(args_num == 4, "Dodavanje firme zahteva ime, adresu i telefon."))
    {
        return;
    }
    char query[MAX_QUERY];
    sprintf (query, "INSERT INTO Firma (Ime, Adresa, Telefon) "
            "VALUES (\"%s\", \"%s\", \"%s\")", args[1], args[2], args[3]);
    execute_query(query);
}

void obrisi_firmu(char **args, int args_num)
{
    if (!assert(args_num == 2, "Brisanje firme zahteva id."))
    {
        return;
    }
    char query[MAX_QUERY];
    sprintf (query, "DELETE FROM Firma WHERE idFirme = %s", args[1]);
    execute_query(query);
}

void usage(void)
{
    printf(
        " Komande:\n"
        " - izlistaj-gradilista [<status>]\n"
        "\tIspisuje informacije o gradilistima [koje imaju zadati status].\n"
        " - dodaj-gradiliste <naziv> <adresa> <status>\n"
        "\tDodaje novo gradiliste u bazu.\n"
        " - obrisi-gradiliste <id>\n"
        "\tBrise gradiliste iz baze.\n"
        " - izlistaj-firme\n"
        "\tIspisuje informacije o firmama.\n"
        " - dodaj-firmu <ime> <adresa> <telefon>\n"
        "\tDodaje novu firmu u bazu.\n"
        " - obrisi-firmu <id>\n"
        "\tBrise firmu iz baze.\n"
        " - query: neki-upit-nad-bazom\n"
        "\tIzvrsava navedeni upit nad bazom.\n"
        " - exit; bye; poy\n"
        "\tZatvara aplikaciju.\n"
    );
}
