#ifndef _H_COMMAND_H
#define _H_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "database.h"
#include "utils.h"

#define MAX_QUERY 256

void execute_command(char *command);
void izlistaj_gradilista(char **args, int args_num);
void dodaj_gradiliste(char **args, int args_num);
void obrisi_gradiliste(char **args, int args_num);
void izlistaj_firme(void);
void dodaj_firmu(char **args, int args_num);
void obrisi_firmu(char **args, int args_num);
void usage(void);

#endif
