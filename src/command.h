#ifndef _H_COMMAND_H
#define _H_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "database.h"
#include "utils.h"
#include "menu.h"

#define MAX_QUERY 1024
#define MAX 64

void enter_and_execute_command(void);

void print_data(void);
void izlistaj_gradilista(void);
void izlistaj_firme(void);

void add_data(void);
void dodaj_gradiliste(void);
void dodaj_firmu(void);
void dodaj_radnika(void);
void dodaj_satnicu_radika(void);
void dodaj_masinu(void);
void dodaj_satnicu_masine(void);
void dodaj_fazu_radova(void);
void dodaj_vrstu_radova(void);
void dodaj_radove_na_gradilistu(void);
void dodaj_trosak(void);
void dodaj_trosak_gradiliste(void);
void dodaj_proizvod(void);
void dodaj_nabavku(void);

void update_data(void);
void azuriraj_gradiliste(void);
void azuriraj_radnika(void);
void azuriraj_firmu(void);
void azuriraj_masinu(void);
void azuriraj_fazu_radova(void);
void azuriraj_vrstu_radova(void);
void azuriraj_trosak(void);
void azuriraj_proizvod(void);

void delete_data(void);

void extra_options(void);
int radnik_sati_po_gradilistu(void);
int masina_sati_po_gradilistu(void);
int firma_sati_po_gradilistu(void);


#endif
