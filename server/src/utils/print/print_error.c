/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** print_error
*/

#include "server.h"

void print_error(const char *error)
{
    dprintf(FD_ERROR, "\033[0;31m");
    dprintf(FD_ERROR, "%s\n", error);
    dprintf(FD_ERROR, "\033[0m");
    if (ERROR_EXIT_PROGRAM) {
        exit(84);
    }
}
