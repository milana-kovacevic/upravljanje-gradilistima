#include "utils.h"

int is_empty(const char *s)
{
    while (*s != '\0')
    {
        if (!isspace((unsigned char)*s))
        {
            return 0;
        }
        s++;
    }
    return 1;
}

char** parse_command_line(char *line, int *n)
{
#ifdef LOG
    printf("Parsing command line... ");
#endif
    *n = 0;
    int is_word = 0;
    int len = strlen(line);
    for(int i = 0; i < len; i++)
    {
        if (isspace(line[i]))
        {
            is_word = 0;
        }
        else
        {
            if (is_word == 0)
            {
                (*n)++;
            }
            is_word = 1;
        }
    }
    
    char **args = malloc(sizeof(char*)*(*n));
    if (args == NULL)
    {
        error_fatal("Malloc error.");
    }
    
    int counter = 0;
    is_word = 0;
    int begin = 0;
    for(int i = 0; i < len; i++)
    {
        if (isspace(line[i]))
        {
            if (is_word == 1)
            {
                args[counter] = strndup(line + begin, i - begin);
                if (args[counter] == NULL)
                {
                    error_fatal("Malloc error.");
                }
                counter++;
            }
            is_word = 0;
            begin = i;
        }
        else
        {
            if (is_word == 0)
            {
                begin = i;
            }
            is_word = 1;
        }
    }
#ifdef LOG
    printf("Done.\n");
#endif
    return args;
}
 
void free_args(char **args, int n)
{
    for(int i = 0; i < n; i++)
    {
        free(args[i]);
    }
    free(args);
    args = NULL;
}

int assert(int condition, const char *msg)
{
    if (!condition)
    {
        error_info("Assert failed. Message: %s", msg);
        return 0;
    }
    return 1;
}

void error_info(char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);
}

void error_fatal(char *format, ...)
{
    va_list arguments;

    va_start (arguments, format);
    vfprintf (stderr, format, arguments);
    va_end (arguments);
    
    exit(EXIT_FAILURE);
}
