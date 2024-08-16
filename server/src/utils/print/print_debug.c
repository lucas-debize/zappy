/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** print_debug
*/

#include "server.h"

void print_debug(const char *str, bool enter)
{
    if (DEBUG) {
        dprintf(FD_DEBUG, "\033[0;32m");
        if (enter)
            dprintf(FD_DEBUG, "%s\n", str);
        else
            dprintf(FD_DEBUG, "%s", str);
        dprintf(FD_DEBUG, "\033[0m");
    }
}
