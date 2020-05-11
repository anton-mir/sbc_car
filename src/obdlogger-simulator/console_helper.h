#ifndef CONSOLE_HELPER_H
#define CONSOLE_HELPER_H

#define COLOR_RED           "\x1b[31m"
#define COLOR_GREEN         "\x1b[32m"
#define COLOR_YELLOW        "\x1b[33m"
#define COLOR_BLUE          "\x1b[34m"
#define COLOR_DEFAULT       "\x1b[0m"

typedef struct CONSOLE_SIZE_STRUCT {
    int cols;
    int rows;
} CONSOLE_SIZE_S;

void print_red(const char *message);
void print_green(const char *message);
void print_yellow(const char *message);
void print_blue(const char *message);
void print_default(const char *message);

void clear_all();

CONSOLE_SIZE_S size_of_console();

#endif