/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** modif_time_unit
*/

#include "server.h"

void modif_time_unit(server_t *server, char **tab)
{
    server->params->freq = atoi(tab[1]);
    dprintf(server->fd_graphic, "sgt %d\n", server->params->freq);
}
