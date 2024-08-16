/*
** EPITECH PROJECT, 2024
** server
** File description:
** print_ok
*/

#include "server.h"

void print_ok(int fd)
{
    write(fd, "ok\n", 3);
}
