/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** print_ko
*/

#include "server.h"

void print_ko(int fd)
{
    write(fd, "ko\n", 3);
}
