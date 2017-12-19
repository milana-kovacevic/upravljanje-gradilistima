#include "utils.h"

int get_option_number(void)
{
    printf("Enter option number: ");
    char line[LINE_MAX];
    if (fgets(line, LINE_MAX - 1, stdin) == NULL || is_empty(line))
    {
        return -1;
    }
    return atoi(line);
}

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
