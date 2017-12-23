#include "menu.h"

void print_main_menu(void)
{
    printf("\n****** MAIN MENU ******\n");
    printf(" Options:\n");
    printf(
        "\t1. Print data\n"
        "\t2. Add\n"
        "\t3. Update\n"
        "\t4. Delete\n"
        "\t5. Extra options\n"
        "\t6. Exit\n"
    );
}

void print_data_menu(void)
{
    printf("\n****** DATA MENU ******\n");
    printf(" Choose entity to print:\n");
    print_entities();
}

void print_add_menu(void)
{
    printf("\n****** ADD MENU ******\n");
    printf(" Choose entity to add:\n");
    print_entities();
}

void print_update_menu(void)
{
    printf("\n****** UPDATE MENU ******\n");
    printf(" Choose entity to update:\n");
    printf(
        "\t1. Gradiliste\n"
        "\t2. Firma\n"
        "\t3. Radnik\n"
        "\t4. Masina\n"
        "\t5. Faza radova\n"
        "\t6. Vrsta radova\n"
        "\t7. Trosak\n"
        "\t8. Proizvod\n"
    );
}

void print_delete_menu(void)
{
    printf("\n****** DELETE MENU ******\n");
    printf(" Choose entity to delete:\n");
    printf(
        "\t1. Gradiliste\n"
        "\t2. Firma\n"
        "\t3. Radnik\n"
        "\t4. Masina\n"
        "\t5. Faza radova\n"
        "\t6. Vrsta radova\n"
        "\t7. Trosak\n"
        "\t8. Proizvod\n"
    );
}

void print_extra_menu(void)
{
    printf("\n****** EXTRA MENU ******\n");
    printf(" Choose extra option:\n");
    printf(
        "\t1. Radnik sati po gradilistu\n"
        "\t2. Masina sati po gradilistu\n"
        "\t3. Firma sati\n"
    );
}

void print_entities(void)
{
    printf(
        "\t1. Gradiliste\n"
        "\t2. Firma\n"
        "\t3. Radnik\n"
        "\t4. Satnica radnika\n"
        "\t5. Masina\n"
        "\t6. Satnica masina\n"
        "\t7. Faza radova\n"
        "\t8. Vrsta radova\n"
        "\t9. Radovi na gradilistu\n"
        "\t10. Trosak\n"
        "\t11. Trosak Gradiliste\n"
        "\t12. Proizvod\n"
        "\t13. Nabavka\n"
    );
}
