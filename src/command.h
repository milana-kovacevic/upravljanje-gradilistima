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

void update_data(void);

void delete_data(void);

void extra_options(void);
void radnik_sati_po_gradilistu(void);
void masina_sati_po_gradilistu(void);


#endif
