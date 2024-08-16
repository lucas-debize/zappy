/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void handle_connect_nbr(server_t *server, client_t *client)
{
    (void) server;
    dprintf(client->fd, "%d\n", client->player->team->free_slots);
}
