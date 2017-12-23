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
            break;
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
            break;
        default:
            printf("Unknown command number.\n");
            break;
    }
}

void dodaj_gradiliste(void)
{
    char naziv[MAX], adresa[MAX], status[MAX];
    // naziv
    printf("Unesi podatke:\n\tNaziv: ");
    if (fgets(naziv, MAX - 1, stdin) == NULL || is_empty(naziv))
    {
        printf("Invalid input.\n");
        return;
    }
    naziv[strlen(naziv)-1] = '\0';
    
    // adresa
    printf("\tAdresa: ");
    if (fgets(adresa, MAX - 1, stdin) == NULL || is_empty(adresa))
    {
        printf("Invalid input.\n");
        return;
    }
    adresa[strlen(adresa)-1] = '\0';
    
    // status
    printf("\tStatus (prazno za default): ");
    if (fgets(status, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    status[strlen(status)-1] = '\0';
    
    char query[MAX_QUERY];
    if (is_empty(status))
    {
        sprintf(query, "INSERT INTO Gradiliste (Naziv, Adresa) "
                "VALUES (\"%s\", \"%s\")", naziv, adresa);
    }
    else
    {
        sprintf(query, "INSERT INTO Gradiliste (Naziv, Adresa, Status) "
                "VALUES (\"%s\", \"%s\", \"%s\")", naziv, adresa, status);
    }
    execute_query(query);
}

void dodaj_firmu(void)
{
    char ime[MAX], adresa[MAX], telefon[MAX];
    char query[MAX_QUERY];
    int offset = 0;
    // ime
    printf("Unesi podatke:\n\tIme: ");
    if (fgets(ime, MAX - 1, stdin) == NULL || is_empty(ime))
    {
        printf("Invalid input.\n");
        return;
    }
    ime[strlen(ime)-1] = '\0';
    offset = sprintf(query, "INSERT INTO Firma (Ime, Adresa, Telefon) "
            "VALUES (\"%s\", ", ime);
    // adresa
    printf("\tAdresa (prazno za null): ");
    if (fgets(adresa, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    adresa[strlen(adresa)-1] = '\0';
    if (is_empty(adresa))
    {
        offset += sprintf(query + offset, "null, ");
    }
    else
    {
        offset += sprintf(query + offset, "\"%s\", ", adresa);
    }
    
    // telefon
    printf("\tTelefon (prazno za null): ");
    if (fgets(telefon, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    telefon[strlen(telefon)-1] = '\0';
    
    if (is_empty(telefon))
    {
        offset += sprintf(query + offset, "null)");
    }
    else
    {
        offset += sprintf(query + offset, "\"%s\")", telefon);
    }
    execute_query(query);
}

void dodaj_radnika(void)
{
    char ime[MAX], prezime[MAX], pozicija[MAX], telefon[MAX], cenaPoSatu[MAX];
    int idFirme;
    char query[MAX_QUERY];
    int offset = 0;
    printf("Unesi ime, prezime, id firme, poziciju: ");
    scanf("%s%s%d%s", ime, prezime, &idFirme, pozicija);
    getchar();
    offset = sprintf(query, "INSERT INTO Radnik (Ime, Prezime, idFirme, Pozicija, Telefon, CenaPoSatu) "
            "VALUES (\"%s\", \"%s\", \"%d\", \"%s\", ", ime, prezime, idFirme, pozicija);
    // telefon
    printf("Telefon (prazno za null): ");
    if (fgets(telefon, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    telefon[strlen(telefon)-1] = '\0';
    if (is_empty(telefon))
    {
        offset += sprintf(query + offset, "null, ");
    }
    else
    {
        offset += sprintf(query + offset, "\"%s\", ", telefon);
    }
    // cena po satu
    printf("CenaPoSatu (prazno za default): ");
    if (fgets(cenaPoSatu, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }    
    if (is_empty(cenaPoSatu))
    {
        offset += sprintf(query + offset, "null)");
    }
    else
    {
        offset += sprintf(query + offset, "%f)", atof(cenaPoSatu));
    }
    execute_query(query);
}

void dodaj_satnicu_radika(void)
{
    int id_radnika, id_gradilista, broj_sati;
    char datum[MAX];
    printf("Unesi id radnika, id gradilista, datum i broj sati: ");
    scanf("%d%d%s%d", &id_radnika, &id_gradilista, datum, &broj_sati);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO SatnicaRadnika VALUES (%d, %d, \"%s\", %d)",
            id_radnika, id_gradilista, datum, broj_sati);
    execute_query(query);
}

void dodaj_masinu(void)
{
    char naziv[MAX], proizvodjac[MAX], potrosnja_goriva[MAX];
    double cena_po_satu;
    char query[MAX_QUERY];
    int offset = 0;

    // naziv
    printf("Unesi podatke:\n\tNaziv: ");
    if (fgets(naziv, MAX - 1, stdin) == NULL || is_empty(naziv))
    {
        printf("Invalid input.\n");
        return;
    }
    naziv[strlen(naziv)-1] = '\0';
    offset = sprintf(query, "INSERT INTO Masina (Naziv, Proizvodjac, PotrosnjaGoriva, CenaPoSatu) "
            "VALUES (\"%s\", ", naziv);

    // proizvodjac
    printf("\tProizvodjac (prazno za null): ");
    if (fgets(proizvodjac, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    proizvodjac[strlen(proizvodjac)-1] = '\0';
    if (is_empty(proizvodjac))
    {
        offset += sprintf(query + offset, "null, ");
    }
    else
    {
        offset += sprintf(query + offset, "\"%s\", ", proizvodjac);
    }

    // potrosnja_goriva
    printf("\tPotrosnja goriva (prazno za null): ");
    if (fgets(potrosnja_goriva, MAX - 1, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }
    potrosnja_goriva[strlen(potrosnja_goriva)-1] = '\0';

    if (is_empty(potrosnja_goriva))
    {
        offset += sprintf(query + offset, "null, ");
    }
    else
    {
        offset += sprintf(query + offset, "%f, ", atof(potrosnja_goriva));
    }

    // cena po satu
    printf("\tCena po satu: ");
    scanf("%lf", &cena_po_satu);
    getchar();
    offset += sprintf(query + offset, "%lf)", cena_po_satu);

    execute_query(query);
}

void dodaj_satnicu_masine(void)
{
    int id_masine, id_gradilista, broj_sati;
    char datum[MAX];
    printf("Unesi id masine, id gradilista, datum i broj sati: ");
    scanf("%d%d%s%d", &id_masine, &id_gradilista, datum, &broj_sati);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO SatnicaMasine VALUES (%d, %d, \"%s\", %d)",
            id_masine, id_gradilista, datum, broj_sati);
    execute_query(query);
}

void dodaj_fazu_radova(void)
{
    char naziv[MAX];
    printf("Unesi podatke:\n\tNaziv faze: ");
    if (fgets(naziv, MAX - 1, stdin) == NULL || is_empty(naziv))
    {
        printf("Invalid input.\n");
        return;
    }
    naziv[strlen(naziv)-1] = '\0';
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO FazaRadova (Naziv) VALUES (\"%s\")", naziv);
    execute_query(query);
}

void dodaj_vrstu_radova(void)
{
    char naziv[MAX];
    printf("Unesi podatke:\n\tNaziv vrste radova: ");
    if (fgets(naziv, MAX - 1, stdin) == NULL || is_empty(naziv))
    {
        printf("Invalid input.\n");
        return;
    }
    naziv[strlen(naziv)-1] = '\0';
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO VrstaRadova (Naziv) VALUES (\"%s\")", naziv);
    execute_query(query);
}

void dodaj_radove_na_gradilistu(void)
{
    int id_gradilista, id_vrste, id_faze;
    char datum[MAX];
    printf("Unesi id gradilista, id vrste radova, id faze radova i datum: ");
    scanf("%d%d%d%s", &id_gradilista, &id_vrste, &id_faze, datum);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO RadoviNaGradilistu (idGradilista, idVrsteRadova, idFazeRadova, Datum) "
            "VALUES (%d, %d, %d, \"%s\")", id_gradilista, id_vrste, id_faze, datum);
    execute_query(query);
}

void dodaj_trosak(void)
{
    char naziv[MAX];
    double cena_po_danu;
    printf("Unesi podatke:\n\tNaziv troska: ");
    if (fgets(naziv, MAX - 1, stdin) == NULL || is_empty(naziv))
    {
        printf("Invalid input.\n");
        return;
    }
    naziv[strlen(naziv)-1] = '\0';
    char query[MAX_QUERY];
    int offset = sprintf(query, "INSERT INTO Trosak (Naziv, CenaPoDanu) VALUES (\"%s\", ", naziv);
    printf("\tCena po danu: ");
    scanf("%lf", &cena_po_danu);
    getchar();
    sprintf(query + offset, "%lf)", cena_po_danu);
    execute_query(query);
}

void dodaj_trosak_gradiliste(void)
{
    int id_gradilista, id_troska;
    char datum[MAX];
    printf("Unesi id gradilista, id troska i datum pocetka: ");
    scanf("%d%d%s", &id_gradilista, &id_troska, datum);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO TrosakGradiliste (idGradilista, idTroska, DatumPocetka) "
            "VALUES (%d, %d, \"%s\")", id_gradilista, id_troska, datum);
    execute_query(query);
}

void dodaj_proizvod(void)
{
    char naziv[MAX], proizvodjac[MAX];
    double cena;
    printf("Unesi naziv, cenu i proizvodjaca: ");
    scanf("%s%lf%s", naziv, &cena, proizvodjac);
    getchar();
    char query[MAX_QUERY];
    sprintf(query, "INSERT INTO Proizvod (Naziv, Cena, Proizvodjac) "
            "VALUES (\"%s\", %lf, \"%s\")", naziv, cena, proizvodjac);
    execute_query(query);
}

void dodaj_nabavku(void)
{
    int id_gradilista, id_proizvoda, kolicina;
    char datum[MAX], napomena[MAX];
    printf("Unesi id gradilista, id proizvoda i kolicinu: ");
    scanf("%d%d%d", &id_gradilista, &id_proizvoda, &kolicina);
    getchar();
    char query[MAX_QUERY];
    int offset = sprintf(query, "INSERT INTO Nabavka (idGradilista, idProizvoda, Kolicina, Datum, Napomena) "
            "VALUES (%d, %d, %d, ", id_gradilista, id_proizvoda, kolicina);
    
    printf("Unesi datum (prazno za danasnji datum): ");
    if (fgets(datum, MAX - 1, stdin) == NULL || is_empty(datum))
    {
        offset += sprintf(query + offset, "null, ");
    }
    else
    {
        datum[strlen(datum) - 1] = '\0';
        offset += sprintf(query + offset, "\"%s\", ", datum);
    }
    
    printf("Unesi napomenu (prazno za null): ");
    if (fgets(napomena, MAX - 1, stdin) == NULL || is_empty(napomena))
    {
        offset += sprintf(query + offset, "null)");
    }
    else
    {
        napomena[strlen(napomena) - 1] = '\0';
        offset += sprintf(query + offset, "\"%s\")", napomena);
    }
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
    int rows_returned;
    print_extra_menu();
    switch(get_option_number())
    {
        case 1:
            rows_returned = radnik_sati_po_gradilistu();
            break;
        case 2:
            rows_returned = masina_sati_po_gradilistu();
            break;
        case 3:
            rows_returned = firma_sati_po_gradilistu();
            break;
        default:
            printf("Unknown command number.\n");
            return;
    }
    if (rows_returned == 1)
    {
        printf("%d row returned.\n", rows_returned);
    }
    else
    {
        printf("%d rows returned.\n", rows_returned);
    }
}

int radnik_sati_po_gradilistu(void)
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
    return execute_query(query);
}

int masina_sati_po_gradilistu(void)
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
    return execute_query(query);
}

int firma_sati_po_gradilistu(void)
{
    printf("Unesite ime firme: ");
    char ime_firme[MAX];
    if (fgets(ime_firme, MAX - 1, stdin) == NULL || is_empty(ime_firme))
    {
        printf("Invalid input.\n");
        return 0;
    }
    ime_firme[strlen(ime_firme)-1] = '\0';
    char query[MAX_QUERY];
    sprintf(query, "SELECT f.Ime, g.Naziv, sum(sr.BrojSati) AS 'Ukupno sati' "
                    "FROM Firma f, Gradiliste g, Radnik r, SatnicaRadnika sr "
                    "WHERE f.Ime = \"%s\" AND f.idFirme = r.idFirme AND "
                        "sr.idRadnika = r.idRadnika AND g.idGradilista = sr.idGradilista "
                    "GROUP BY f.Ime, f.idFirme, g.Naziv", ime_firme
           );
    return execute_query(query);
}
