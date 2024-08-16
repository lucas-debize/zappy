/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time_unit
*/

#include "server.h"

void time_unit(server_t *server, char **tab)
{
    (void) tab;

    dprintf(server->fd_graphic, "sgt %d\n", server->params->freq);
}
