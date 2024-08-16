/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward
*/

#include "server.h"

void handle_right(server_t *server, client_t *client)
{
    char str[30] = "";

    client->player->orientation = (client->player->orientation + 1) % 4;
    print_ok(client->fd);
    snprintf(str, sizeof(str), "ppo %d %d %d %d\n", client->fd,
        client->player->pos.x,
        client->player->pos.y, client->player->orientation + 1);
    write_to_graphic(server, str);
}
