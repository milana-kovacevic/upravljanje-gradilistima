#ifndef _H_UTILS_H
#define _H_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

//#define LOG
#define LINE_MAX 512

int get_option_number(void);
int is_empty(const char *s);

int assert(int condition, const char *msg);
void error_fatal(char *format, ...);
void error_info(char *format, ...);

#endif
