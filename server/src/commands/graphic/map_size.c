/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_size
*/

#include "server.h"

void map_size(server_t *server, char **tab)
{
    (void) tab;
    dprintf(server->fd_graphic, "msz %d %d\n",
    server->params->width, server->params->height);
}
