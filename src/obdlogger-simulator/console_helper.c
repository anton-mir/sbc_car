#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>

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

CONSOLE_SIZE_S size_of_console()
{
    struct winsize ws;
    CONSOLE_SIZE_S size = { 0 };
    int fd = open("/dev/tty", O_RDWR);
    if (fd < 0) {
        print_red("Open terminal failed!");
        perror("ERROR");
        return size;
    }

    if (ioctl(fd, TIOCGWINSZ, &ws) < 0) {
        print_red("Console size get failed!");
        perror("ERROR");
        return size;
    }

    size.cols = ws.ws_col;
    size.rows = ws.ws_row;

    close(fd);
}