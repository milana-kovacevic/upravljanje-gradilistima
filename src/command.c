#include "command.h"

void enter_and_execute_command(void)
{
    switch(get_option_number())
    {
        case 1:
            print_data();
            break;
        case 2:
            add_data();
            break;
        case 3:
            update_data();
            break;
        case 4:
            delete_data();
            break;
        case 5:
            extra_options();
            break;
        case 6:
            close_db_connection();
            printf("Bye!\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Unknown option number.\n");
            break;
    }
}

void print_data(void)
{
    print_data_menu();
    int rows_returned = 0;
    switch(get_option_number())
    {
        case 1:
            rows_returned = execute_query("SELECT * FROM Gradiliste");
            break;
        case 2:
            rows_returned = execute_query("SELECT * FROM Firma");
            break;
        case 3:
            rows_returned = execute_query("SELECT * FROM Radnik");
            break;
        case 4:
            rows_returned = execute_query("SELECT * FROM SatnicaRadnika");
            break;
        case 5:
            rows_returned = execute_query("SELECT * FROM Masina");
            break;
        case 6:
            rows_returned = execute_query("SELECT * FROM SatnicaMasine");
            break;
        case 7:
            rows_returned = execute_query("SELECT * FROM FazaRadova");
            break;
        case 8:
            rows_returned = execute_query("SELECT * FROM VrstaRadova");
            break;
        case 9:
            rows_returned = execute_query("SELECT * FROM RadoviNaGradilistu");
            break;
        case 10:
            rows_returned = execute_query("SELECT * FROM Trosak");
            break;
        case 11:
            rows_returned = execute_query("SELECT * FROM TrosakGradiliste");
            break;
        case 12:
            rows_returned = execute_query("SELECT * FROM Proizvod");
            break;
        case 13:
            rows_returned = execute_query("SELECT * FROM Nabavka");
            break;
        default:
            printf("Unknown command number.\n");
            return;
    }
    printf("%d rows returned.\n", rows_returned);
}


void add_data(void)
{
    print_add_menu();
    switch(get_option_number())
    {
        case 1:
            dodaj_gradiliste();
            break;
        case 2:
            dodaj_firmu();
            break;/*
        case 3:
            dodaj_radnika();
            break;
        case 4:
            dodaj_satnicu_radika();
            break;
        case 5:
            dodaj_masinu();
            break;
        case 6:
            dodaj_satnicu_masine();
            break;
        case 7:
            dodaj_fazu_radova();
            break;
        case 8:
            dodaj_vrstu_radova();
            break;
        case 9:
            dodaj_radove_na_gradilistu();
            break;
        case 10:
            dodaj_trosak();
            break;
        case 11:
            dodaj_trosak_gradiliste();
            break;
        case 12:
            dodaj_proizvod();
            break;
        case 13:
            dodaj_nabavku();
            break;*/
        default:
            printf("Unknown command number.\n");
            break;
    }
    getchar();
}

void dodaj_gradiliste(void)
{
    printf("Unesi naziv, adresu i status gradilista: ");
    char naziv[MAX], adresa[MAX], status[MAX];
    scanf("%s%s%s", naziv, adresa, status);
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO Gradiliste (Naziv, Adresa, Status) "
            "VALUES (\"%s\", \"%s\", \"%s\")", naziv, adresa, status);
    execute_query(query);
}

void dodaj_firmu(void)
{
    printf("Unesi ime, adresu i telefon firme: ");
    char ime[MAX], adresa[MAX], telefon[MAX];
    scanf("%s%s%s", ime, adresa, telefon);
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO Firma (Ime, Adresa, Telefon) "
            "VALUES (\"%s\", \"%s\", \"%s\")", ime, adresa, telefon);
    execute_query(query);
}

void update_data(void)
{
    print_update_menu();
    
}

void delete_data(void)
{
    print_delete_menu();
    int option_number = get_option_number();
    printf("Id to delete: ");
    int id;
    scanf("%d", &id);
    getchar();
    char query[MAX_QUERY];
    switch(option_number)
    {
        case 1:
            sprintf (query, "DELETE FROM Gradiliste WHERE idGradilista = %d", id);
            break;
        case 2:
            sprintf (query, "DELETE FROM Firma WHERE idFirme = %d", id);
            break;
        case 3:
            sprintf (query, "DELETE FROM Radnik WHERE idRadnika = %d", id);
            break;
        case 4:
            sprintf (query, "DELETE FROM Masina WHERE idMasine = %d", id);
            break;
        case 5:
            sprintf (query, "DELETE FROM FazaRadova WHERE idFazeRadova = %d", id);
            break;
        case 6:
            sprintf (query, "DELETE FROM VrstaRadova WHERE idVrsteRadova = %d", id);
            break;
        case 7:
            sprintf (query, "DELETE FROM Trosak WHERE idTroska = %d", id);
            break;
        case 8:
            sprintf (query, "DELETE FROM Proizvod WHERE idProizvoda = %d", id);
            break;
        default:
            printf("Unknown command number.\n");
            return;
    }
    int rows_deleted = execute_query(query);
    if (rows_deleted == 1)
    {
        printf("%d row deleted.\n", rows_deleted);
    }
    else
    {
        printf("%d rows deleted.\n", rows_deleted);
    }
}

void extra_options(void)
{
    print_extra_menu();
    switch(get_option_number())
    {
        case 1:
            radnik_sati_po_gradilistu();
            break;
        case 2:
            masina_sati_po_gradilistu();
            break;
        default:
            printf("Unknown command number.\n");
            return;
    }
}

void radnik_sati_po_gradilistu(void)
{
    char from[MAX], to[MAX];
    printf("Unesite pocetni datum: ");
    scanf("%s", from);
    printf("Unesite krajnji datum: ");
    scanf("%s", to);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "SELECT r.Ime, r.Prezime, g.Naziv, sum(sr.BrojSati) AS 'Ukupno sati' "
                    "FROM Radnik r, Gradiliste g, SatnicaRadnika sr "
                    "WHERE r.idRadnika = sr.idRadnika AND g.idGradilista = sr.idGradilista "
                    " AND sr.Datum >= '%s' AND sr.Datum <= '%s' "
                    "GROUP BY r.idRadnika, r.Ime, r.Prezime, g.idGradilista, g.Naziv", from, to
           );
    int rows_returned = execute_query(query);
    printf("%d rows returned.\n", rows_returned);
}

void masina_sati_po_gradilistu(void)
{
    char from[MAX], to[MAX];
    printf("Unesite pocetni datum: ");
    scanf("%s", from);
    printf("Unesite krajnji datum: ");
    scanf("%s", to);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "SELECT m.Naziv, g.Naziv, sum(sm.BrojSati) AS 'Ukupno sati' "
                    "FROM Masina m, Gradiliste g, SatnicaMasine sm "
                    "WHERE m.idMasine = sm.idMasine AND g.idGradilista = sm.idGradilista "
                    " AND sm.Datum >= '%s' AND sm.Datum <= '%s' "
                    "GROUP BY m.idMasine, m.Naziv, g.idGradilista, g.Naziv", from, to
           );
    int rows_returned = execute_query(query);
    printf("%d rows returned.\n", rows_returned);
}
