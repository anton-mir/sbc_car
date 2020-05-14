#include <stdio.h>
#include <unistd.h>

#include "console_helper.h"

void print_red(const char *message)
{
    printf(COLOR_RED "%s" COLOR_DEFAULT "\n", message);
}
void print_green(const char *message)
{
    printf(COLOR_GREEN "%s" COLOR_DEFAULT "\n", message);
}
void print_yellow(const char *message)
{
    printf(COLOR_YELLOW "%s" COLOR_DEFAULT "\n", message);
}
void print_blue(const char *message)
{
    printf(COLOR_BLUE "%s" COLOR_DEFAULT "\n", message);
}
void print_default(const char *message)
{
    printf(COLOR_DEFAULT "%s" COLOR_DEFAULT "\n", message);
}

void clear_all()
{
    printf("\033[H\033[2J"); 
    fflush(stdout);
}
