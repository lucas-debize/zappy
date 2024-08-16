/*
** EPITECH PROJECT, 2024
** server
** File description:
** connection_new_player
*/

#include "server.h"

void connection_new_player(server_t *server, client_t *client)
{
    if (server->fd_graphic == 0)
        return;
    dprintf(server->fd_graphic, "pnw %d %d %d %d %d %s\n", client->fd, client->player->pos.x,
            client->player->pos.y, client->player->orientation + 1, client->player->level,
            client->player->team->team_name);
    if (server->params->display_egg)
        dprintf(server->fd_graphic, "ebo %d\n", client->player->egg->id);
}
